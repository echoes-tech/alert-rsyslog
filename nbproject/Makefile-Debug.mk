#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=DISTCC_FALLBACK=0 distcc
CXX=DISTCC_FALLBACK=0 distcc
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux-x86
CND_DLIB_EXT=so
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/324370602/Conf.o \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/src/SDElement.o \
	${OBJECTDIR}/src/SDElementProp.o \
	${OBJECTDIR}/src/SDElementRes.o \
	${OBJECTDIR}/src/SDID.o \
	${OBJECTDIR}/src/SDParam.o \
	${OBJECTDIR}/src/SDParamRes.o \
	${OBJECTDIR}/src/StructuredData.o \
	${OBJECTDIR}/src/SyslogInsert.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=-pedantic
CXXFLAGS=-pedantic

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-L../dbo/dist/Debug_SharedObject/GNU-Linux-x86 -ldbo -lwt -lboost_regex -lboost_system

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/rsyslog

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/rsyslog: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/rsyslog ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/_ext/324370602/Conf.o: /home/fpo/Dev/echoes-alert/rsyslog/src/Conf.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/324370602
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -Iinclude -I../dbo/include -std=c++11 -pedantic -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/324370602/Conf.o /home/fpo/Dev/echoes-alert/rsyslog/src/Conf.cpp

${OBJECTDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -Iinclude -I../dbo/include -std=c++11 -pedantic -MMD -MP -MF $@.d -o ${OBJECTDIR}/main.o main.cpp

${OBJECTDIR}/src/SDElement.o: src/SDElement.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -Iinclude -I../dbo/include -std=c++11 -pedantic -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/SDElement.o src/SDElement.cpp

${OBJECTDIR}/src/SDElementProp.o: src/SDElementProp.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -Iinclude -I../dbo/include -std=c++11 -pedantic -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/SDElementProp.o src/SDElementProp.cpp

${OBJECTDIR}/src/SDElementRes.o: src/SDElementRes.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -Iinclude -I../dbo/include -std=c++11 -pedantic -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/SDElementRes.o src/SDElementRes.cpp

${OBJECTDIR}/src/SDID.o: src/SDID.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -Iinclude -I../dbo/include -std=c++11 -pedantic -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/SDID.o src/SDID.cpp

${OBJECTDIR}/src/SDParam.o: src/SDParam.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -Iinclude -I../dbo/include -std=c++11 -pedantic -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/SDParam.o src/SDParam.cpp

${OBJECTDIR}/src/SDParamRes.o: src/SDParamRes.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -Iinclude -I../dbo/include -std=c++11 -pedantic -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/SDParamRes.o src/SDParamRes.cpp

${OBJECTDIR}/src/StructuredData.o: src/StructuredData.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -Iinclude -I../dbo/include -std=c++11 -pedantic -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/StructuredData.o src/StructuredData.cpp

${OBJECTDIR}/src/SyslogInsert.o: src/SyslogInsert.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -Iinclude -I../dbo/include -std=c++11 -pedantic -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/SyslogInsert.o src/SyslogInsert.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/rsyslog

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
