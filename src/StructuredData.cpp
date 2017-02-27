/**
 * @file StructuredData.cpp
 * @author Thomas Saquet, Florent Poinsaut
 * @date 
 * @brief File containing example of doxygen usage for quick reference.
 *
 * Alert - rsyslog is a part of the Alert software
 * Copyright (C) 2013-2017
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301  USA
 * 
 */

#include "StructuredData.h"

using namespace std;

StructuredData::StructuredData(const string &content, Wt::Dbo::ptr<Echoes::Dbo::Syslog> sloWtDBOPtr, Echoes::Dbo::Session &session)
{
    setContent(content);

    if (_content.compare(""))
    {
        splitSDElements(sloWtDBOPtr, session);
        if (_sdElementProp)
        {
            if (_sdElementProp->getProbeWtDBOPtr().id() > 0 && _sdElementProp->isValidToken(session))
                createIVAs(sloWtDBOPtr, session);
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

void StructuredData::splitSDElements(Wt::Dbo::ptr<Echoes::Dbo::Syslog> sloWtDBOPtr, Echoes::Dbo::Session &session)
{
    // Warning : this method doesn't work well if the value of SD-Params can contain the chars '[' ']'
    
    string sdTmp(_content);
    vector<string> sSDElements;

    // SD-Element example : [prop@40311 ver=2 probe=0 token="abcdefghijklmo0123456789"][res1@40311 offset=2 4-1-3-4-1-1-1="U3VjaCBJbnN0YW5jZSBjdXJyZW50bHkgZXhpc3RzIGF0IHRoaXMgT0lE" 4-1-3-4-2-1-1="U3VjaCBJbnN0YW5jZSBjdXJyZW50bHkgZXhpc3RzIGF0IHRoaXMgT0lE"]
    // nouveau :            [prop@40311 ver=3 probe=0 token="abcdefghijklmo0123456789"][res1@40311 offset=2 lotNum=12 lineNum=7 22="URL_Encode(data)"]
    
    boost::erase_all(sdTmp, "[");
    
    // Example : prop@40311 ver=2 probe=0 token="abcdefghijklmo0123456789"]res1@40311 offset=2 4-1-3-4-1-1-1="U3VjaCBJbnN0YW5jZSBjdXJyZW50bHkgZXhpc3RzIGF0IHRoaXMgT0lE" 4-1-3-4-2-1-1="U3VjaCBJbnN0YW5jZSBjdXJyZW50bHkgZXhpc3RzIGF0IHRoaXMgT0lE"]
    // nouveau : prop@40311 ver=3 probe=0 token="abcdefghijklmo0123456789"]res1@40311 offset=2 lotNum=12 lineNum=7 22="URL_Encode(data)"]

    boost::split(sSDElements, sdTmp, boost::is_any_of("]"), boost::token_compress_on);
    // Examples :
    // prop@40311 ver=2 probe=0 token="abcdefghijklmo0123456789"
    // res1@40311 offset=2 4-1-3-4-1-1-1="U3VjaCBJbnN0YW5jZSBjdXJyZW50bHkgZXhpc3RzIGF0IHRoaXMgT0lE" 4-1-3-4-2-1-1="U3VjaCBJbnN0YW5jZSBjdXJyZW50bHkgZXhpc3RzIGF0IHRoaXMgT0lE"
    // nouveau : 
    // prop@40311 ver=3 probe=0 token="abcdefghijklmo0123456789
    // res1@40311 offset=2 lotNum=12 lineNum=7 22="URL_Encode(data)"
    
    for (unsigned i(0); i < sSDElements.size() - 1; ++i)
    {
        SDElement sdElement(sSDElements[i]);

        if(!sdElement.getSDID().getName().compare("prop"))
            setSDElementProp(SDElementProp(sSDElements[i], sloWtDBOPtr, session));
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

void StructuredData::createIVAs(Wt::Dbo::ptr<Echoes::Dbo::Syslog> sloWtDBOPtr, Echoes::Dbo::Session &session)
{
    bool isPartial = false;

    if (sloWtDBOPtr)
    {
        try
        {   
            Wt::Dbo::Transaction transaction(session);

            sloWtDBOPtr.modify()->state = 1;

            transaction.commit();
        }
        catch (Wt::Dbo::Exception e)
        {
            logger.entry("error") << "[StructuredData] " << e.what();
            return;
        }

        for (unsigned i(0); i < _sdElementsRes.size(); ++i)
        {
            const Wt::WDateTime creationDate = sloWtDBOPtr->sentDate.addSecs(_sdElementsRes[i].getOffset());
            const vector<SDParamRes> sdParamsRes = _sdElementsRes[i].getSDParamsRes();

            for (unsigned j(0); j < sdParamsRes.size() ; ++j)
            {
                Echoes::Dbo::InformationValue *informationValueToAdd = new Echoes::Dbo::InformationValue();
                const long long idIda = sdParamsRes[j].getIdaId();
//                const long long idPlugin = sdParamsRes[j].getIDPlugin();
//                const long long idSource = sdParamsRes[j].getIDSource();
//                const long long idSearch = sdParamsRes[j].getIDSearch();
//                const int valueNum = sdParamsRes[j].getValueNum();

                const string value = Wt::Utils::urlDecode(sdParamsRes[j].getValue());

                informationValueToAdd->lotNumber = _sdElementsRes[i].getLotNumber();
                informationValueToAdd->lineNumber = _sdElementsRes[i].getLineNumber();

                try
                {   
                    Wt::Dbo::Transaction transaction(session);

                    
                    // we have to check wether the asset exists or not (been deleted ?)
                    Wt::Dbo::ptr<Echoes::Dbo::InformationData> idaPtr = session.find<Echoes::Dbo::InformationData>()
                            .where(QUOTE(TRIGRAM_INFORMATION_DATA ID) " = ?").bind(idIda)
                            .where(QUOTE(TRIGRAM_INFORMATION_DATA SEP "DELETE") " IS NULL")
                            .limit(1);

                    if (!idaPtr)
                    {
                        logger.entry("error") << "[StructuredData] Ida with id : " << idIda << " doesn't exist.";
                        delete informationValueToAdd;
                        informationValueToAdd = NULL;
                        isPartial = true;
                        continue;
                    }

//                    // we verify the unit of the collected information before saving it linked to an information entry.   
//                    Wt::Dbo::ptr<Echoes::Dbo::SearchUnit> seuPtr = session.find<Echoes::Dbo::SearchUnit>()
//                            .where("\"PLG_ID_PLG_ID\" = ?").bind(idPlugin)
//                            .where("\"SRC_ID\" = ?").bind(idSource)
//                            .where("\"SEA_ID\" = ?").bind(idSearch)
//                            .where("\"INF_VALUE_NUM\" = ?").bind(valueNum)
//                            .limit(1); 
//
//                    if (!seuPtr)
//                    {
//                        logger.entry("error") << "[StructuredData] No search unit retrieved for: "
//                                    << " Plugin ID = " << idPlugin
//                                    << ", Source ID = " << idSource
//                                    << ", Search ID = " << idSearch
//                                    << ", Value Number = " << valueNum;
//                        delete informationValueToAdd;
//                        informationValueToAdd = NULL;
//                        isPartial = true;
//                        continue;
//                    }

                    logger.entry("debug") << "[StructuredData] looking for INF";
                    Wt::Dbo::ptr<Echoes::Dbo::Information> infPtr = idaPtr->information;
//                    session.find<Echoes::Dbo::Information>()
//                            .where("\"PLG_ID_PLG_ID\" = ?").bind(idPlugin)
//                            .where("\"SRC_ID\" = ?").bind(idSource)
//                            .where("\"SEA_ID\" = ?").bind(idSearch)
//                            .where("\"INF_VALUE_NUM\" = ?").bind(valueNum)
//                            .where("\"INU_ID_INU_ID\" = ?").bind(seuPtr->informationUnit.id())
//                            .limit(1);

                    if (!infPtr)
                    {
                        logger.entry("error") << "[StructuredData] No information retrieved for: "
                                << " Ida ID = " << idIda;
                        delete informationValueToAdd;
                        informationValueToAdd = NULL;
                        isPartial = true;
                        continue;
                    }

                    logger.entry("debug") << "[StructuredData] This value is a number ?";
                    if (infPtr->informationUnit->unitType.id() == Echoes::Dbo::EInformationUnitType::NUMBER)
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
                                    << " idaId : " << idIda;
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

                    informationValueToAdd->informationData = idaPtr;
                    informationValueToAdd->value = value;
                    informationValueToAdd->creationDate = creationDate;
                    informationValueToAdd->syslog = sloWtDBOPtr;

                    if (calculate.empty())
                        informationValueToAdd->state = 0;
                    else
                        informationValueToAdd->state = 9;

                    logger.entry("debug") << "[StructuredData] ivaPtr creation";
                    Wt::Dbo::ptr<Echoes::Dbo::InformationValue> ivaPtr = session.add<Echoes::Dbo::InformationValue>(informationValueToAdd);
                    ivaPtr.flush();
                    logger.entry("debug") << "[StructuredData] IVA " << ivaPtr.id() << " created";

                    transaction.commit();
                }
                catch (Wt::Dbo::Exception e)
                {
                    logger.entry("error") << "[StructuredData] " << e.what();
                    return;
                }
            }
        }

        try
        {   
            Wt::Dbo::Transaction transaction(session);

            if (isPartial)
            {   
                logger.entry("info") << "[StructuredData] SLO " << sloWtDBOPtr.id() << " partially converted into IVA";
                sloWtDBOPtr.modify()->state = 3;
            }
            else
            {
                logger.entry("debug") << "[StructuredData] SLO " << sloWtDBOPtr.id() << " totally converted into IVA";
                sloWtDBOPtr.modify()->state = 2;
            }

            transaction.commit();
        }
        catch (Wt::Dbo::Exception e)
        {
            logger.entry("error") << "[StructuredData] " << e.what();
            return;
        }
    }
    else
        logger.entry("error") << "[StructuredData] sloWtDBOPtr doesn't exist.";

    return;
}
