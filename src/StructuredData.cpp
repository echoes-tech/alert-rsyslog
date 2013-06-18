/* 
 * StructuredData Parser
 * @author ECHOES Technologies (FPO)
 * @date 14/03/2013
 * 
 * THIS PROGRAM IS CONFIDENTIAL AND PROPRIETARY TO ECHOES TECHNOLOGIES SAS
 * AND MAY NOT BE REPRODUCED, PUBLISHED OR DISCLOSED TO OTHERS WITHOUT
 * COMPANY AUTHORIZATION.
 * 
 * COPYRIGHT 2013 BY ECHOES TECHNOLGIES SAS
 * 
 */

#include "StructuredData.h"

using namespace std;

StructuredData::StructuredData(const string &content, const long long &syslogID, Session &session)
{
    setContent(content);

    if (_content.compare(""))
    {
        splitSDElements(syslogID, session);
        if (_sdElementProp)
        {
            if (_sdElementProp->getProbeWtDBOPtr().id() > 0 && _sdElementProp->isValidToken(session))
                createIVAs(syslogID, session);
        }
        else
            logger.entry("error") << "[StructuredData] SD Element Prop is empty";
    }
    else
        logger.entry("error") << "[StructuredData] Content is empty";
}

StructuredData::StructuredData(const StructuredData& orig)
{
    setContent(orig.getContent());
    setSDElementsRes(orig.getSDElementsRes());
    setSDElementProp(orig.getSDElementProp());
}

StructuredData::~StructuredData()
{
}

void StructuredData::setContent(string content)
{
    _content = content;

    return;
}
 
string StructuredData::getContent() const
{
    return _content;
}

void StructuredData::splitSDElements(const long long &syslogID, Session &session)
{
    // Warning : this method doesn't work well if the value of SD-Params can contain the chars '[' ']'
    
    string sdTmp(_content);
    vector<string> sSDElements;

    // SD-Element example : [prop@40311 ver=2 probe=0 token="abcdefghijklmo0123456789"][res1@40311 offset=2 4-1-3-4-1-1-1="U3VjaCBJbnN0YW5jZSBjdXJyZW50bHkgZXhpc3RzIGF0IHRoaXMgT0lE" 4-1-3-4-2-1-1="U3VjaCBJbnN0YW5jZSBjdXJyZW50bHkgZXhpc3RzIGF0IHRoaXMgT0lE"]
    
    boost::erase_all(sdTmp, "[");
    
    // Example : prop@40311 ver=2 probe=0 token="abcdefghijklmo0123456789"]res1@40311 offset=2 4-1-3-4-1-1-1="U3VjaCBJbnN0YW5jZSBjdXJyZW50bHkgZXhpc3RzIGF0IHRoaXMgT0lE" 4-1-3-4-2-1-1="U3VjaCBJbnN0YW5jZSBjdXJyZW50bHkgZXhpc3RzIGF0IHRoaXMgT0lE"]

    boost::split(sSDElements, sdTmp, boost::is_any_of("]"), boost::token_compress_on);
    // Examples :
    // prop@40311 ver=2 probe=0 token="abcdefghijklmo0123456789"
    // res1@40311 offset=2 4-1-3-4-1-1-1="U3VjaCBJbnN0YW5jZSBjdXJyZW50bHkgZXhpc3RzIGF0IHRoaXMgT0lE" 4-1-3-4-2-1-1="U3VjaCBJbnN0YW5jZSBjdXJyZW50bHkgZXhpc3RzIGF0IHRoaXMgT0lE"

    for (unsigned i(0); i < sSDElements.size() - 1; ++i)
    {
        SDElement sdElement(sSDElements[i]);

        if(!sdElement.getSDID().getName().compare("prop"))
            setSDElementProp(SDElementProp(sSDElements[i], syslogID, session));
        else
            addSDElementRes(SDElementRes(sSDElements[i]));
    }

    return;
}

void StructuredData::setSDElementsRes(vector<SDElementRes> sdElementsRes)
{
    _sdElementsRes = sdElementsRes;
    return;
}

void StructuredData::addSDElementRes(const SDElementRes &sdElementRes)
{
    _sdElementsRes.push_back(sdElementRes);
    return;
}

vector<SDElementRes> StructuredData::getSDElementsRes() const
{
    return _sdElementsRes;
}

void StructuredData::setSDElementProp(SDElementProp sdElementProp)
{
    _sdElementProp = sdElementProp;
    return;
}

SDElementProp StructuredData::getSDElementProp() const
{
    return *_sdElementProp;
}

void StructuredData::createIVAs(const long long &syslogID, Session &session)
{
    bool isPartial = false;

    try
    {   
        Wt::Dbo::Transaction transaction(session);

        Wt::Dbo::ptr<Syslog> sloPtr = session.find<Syslog>().where("\"SLO_ID\" = ?").bind(syslogID);

        if (sloPtr)
        {
            sloPtr.modify()->state = 1;
            sloPtr.flush();
            const Wt::WDateTime sendDate = sloPtr->sentDate;

            for (unsigned i(0); i < _sdElementsRes.size(); ++i)
            {
                const Wt::WDateTime creationDate = sendDate.addSecs(_sdElementsRes[i].getOffset());
                const vector<SDParamRes> sdParamsRes = _sdElementsRes[i].getSDParamsRes();

                for (unsigned j(0); j < sdParamsRes.size() ; ++j)
                {
                    InformationValue *informationValueToAdd = new InformationValue();
                    const long long idAsset = sdParamsRes[j].getIDAsset();
                    const long long idPlugin = sdParamsRes[j].getIDPlugin();
                    const long long idSource = sdParamsRes[j].getIDSource();
                    const long long idSearch = sdParamsRes[j].getIDSearch();
                    const int valueNum = sdParamsRes[j].getValueNum();

                    const string value = Wt::Utils::base64Decode(sdParamsRes[j].getValue());

                    informationValueToAdd->lotNumber = sdParamsRes[j].getLotNumber();
                    informationValueToAdd->lineNumber = sdParamsRes[j].getLineNumber();

                    // we have to check wether the asset exists or not (been deleted ?)
                    Wt::Dbo::ptr<Asset> astPtr = session.find<Asset>()
                            .where("\"AST_ID\" = ?").bind(idAsset)
                            .where("\"AST_DELETE\" IS NULL")
                            .limit(1);

                    if (!astPtr)
                    {
                        logger.entry("error") << "[StructuredData] Asset with id : " << idAsset << " doesn't exist.";
                        delete informationValueToAdd;
                        informationValueToAdd = NULL;
                        isPartial = true;
                        continue;
                    }

                    // we verify the unit of the collected information before saving it linked to an information entry.   
                    Wt::Dbo::ptr<SearchUnit> seuPtr = session.find<SearchUnit>()
                            .where("\"PLG_ID_PLG_ID\" = ?").bind(idPlugin)
                            .where("\"SRC_ID\" = ?").bind(idSource)
                            .where("\"SEA_ID\" = ?").bind(idSearch)
                            .where("\"INF_VALUE_NUM\" = ?").bind(valueNum)
                            .limit(1); 

                    if (!seuPtr)
                    {
                        logger.entry("error") << "[StructuredData] No search unit retrieved for: "
                                    << " Plugin ID = " << idPlugin
                                    << ", Source ID = " << idSource
                                    << ", Search ID = " << idSearch
                                    << ", Value Number = " << valueNum;
                        delete informationValueToAdd;
                        informationValueToAdd = NULL;
                        isPartial = true;
                        continue;
                    }

                    logger.entry("debug") << "[StructuredData] looking for INF";
                    Wt::Dbo::ptr<Information2> infPtr = session.find<Information2>()
                            .where("\"PLG_ID_PLG_ID\" = ?").bind(idPlugin)
                            .where("\"SRC_ID\" = ?").bind(idSource)
                            .where("\"SEA_ID\" = ?").bind(idSearch)
                            .where("\"INF_VALUE_NUM\" = ?").bind(valueNum)
                            .where("\"INU_ID_INU_ID\" = ?").bind(seuPtr->informationUnit.id())
                            .limit(1);

                    if (!infPtr)
                    {
                        logger.entry("error") << "[StructuredData] No information retrieved for: "
                                << " Plugin ID = " << idPlugin
                                << ", Source ID = " << idSource
                                << ", Search ID = " << idSearch
                                << ", Value Number = " << valueNum
                                << ", Unit ID = " << seuPtr->informationUnit.id();
                        delete informationValueToAdd;
                        informationValueToAdd = NULL;
                        isPartial = true;
                        continue;
                    }

                    infPtr.reread();

                    logger.entry("debug") << "[StructuredData] This value is a number ?";
                    if (infPtr->pk.unit->unitType.id() == Enums::NUMBER)
                    {
                        try
                        {
                            boost::lexical_cast<long double>(value);
                            logger.entry("debug") << "[StructuredData] Yes, this value is a number.";
                        }
                        catch(boost::bad_lexical_cast &)
                        {
                            logger.entry("error")
                                    << "[StructuredData] Values :" << value
                                    << " seaId : " << idSearch
                                    << " srcId : " << idSource
                                    << " plgId : " << idPlugin
                                    << " valueNum : " << valueNum
                                    << " astId: " << idAsset
                                    << " must be a number";
                            delete informationValueToAdd;
                            informationValueToAdd = NULL;
                            isPartial = true;
                            continue;
                        }
                    }
                    else
                        logger.entry("debug") << "[StructuredData] No, this value isn't a number.";

                    // we check whether we have to calculate something about the information
                    logger.entry("debug") << "[StructuredData] Calculate this INF ?";
                    Wt::WString calculate = Wt::WString::Empty;
                    if (infPtr->calculate)
                    {
                        if (!infPtr->calculate.get().empty())
                        {
                            calculate = infPtr->calculate.get();
                            logger.entry("debug") << "[StructuredData] Calculation found: " << calculate;
                        }
                        else
                        {
                            logger.entry("error") << "[StructuredData] No calculation found, should have";
                            delete informationValueToAdd;
                            informationValueToAdd = NULL;
                            isPartial = true;
                            continue;
                        }
                    }
                    else
                        logger.entry("debug") << "[StructuredData] No calculation required";

                    informationValueToAdd->information = infPtr;
                    informationValueToAdd->value = value;
                    informationValueToAdd->creationDate = creationDate;
                    informationValueToAdd->asset = astPtr;
                    informationValueToAdd->syslog = sloPtr;

                    if (calculate.empty())
                        informationValueToAdd->state = 0;
                    else
                        informationValueToAdd->state = 9;

                    logger.entry("debug") << "[StructuredData] ivaPtr creation";
                    Wt::Dbo::ptr<InformationValue> ivaPtr = session.add<InformationValue>(informationValueToAdd);
                    ivaPtr.flush();
                    logger.entry("debug") << "[StructuredData] IVA " << ivaPtr.id() << " created";
                }
            }

            if (isPartial)
            {   
                logger.entry("info") << "[StructuredData] SLO " << syslogID << " partially converted into IVA";
                sloPtr.modify()->state = 3;
            }
            else
            {
                logger.entry("debug") << "[StructuredData] SLO " << syslogID << " totally converted into IVA";
                sloPtr.modify()->state = 2;
            }
        }
        else
            logger.entry("error") << "[StructuredData] Syslog with id : " << syslogID << " doesn't exist.";

        transaction.commit();
    }
    catch (Wt::Dbo::Exception e)
    {
        logger.entry("error") << "[StructuredData] " << e.what();
    }

    return;
}

