################################################################################
# ModuleName  : Demo
# $File$
# $Author$
# $Date$
################################################################################
# Description :
# usage: python clConfig.py <args>
# create clCompConfig.h
#
###############################################################################
import sys
import string
import os
import xml.dom.minidom
from string import Template
import time
import getpass
import shutil

clConfigHeaderFileTemplate = Template("""
/*******************************************************************************
*
* This headerfile is auto-generated by ClovisWorks
*
* clCompConfig.h for ${cpmName}
*
* 
* Date: ${DateTime}
* User: ${User} 
* 
*
********************************************************************************/

#ifndef CL_COMP_CFG
#define CL_COMP_CFG

#include <clCommon.h>   
#include <clEoApi.h>                                                                                                                          
                                                                                                                             
#define COMP_NAME       "${cpmName}"
#define COMP_EO_NAME    "${eoName}"

#define HAS_EO_SERVICES ${hasEOServices}

#define COMP_EO_THREAD_PRIORITY ${eoThreadPriority}
#define COMP_EO_NUM_THREAD ${eoNumThread}
#define COMP_IOC_PORT ${iocPort}
#define COMP_EO_USER_CLIENT_ID (CL_EO_USER_CLIENT_ID_START + ${maxNoClients})
#define COMP_EO_USE_THREAD_MODEL ${threadPolicy}
                                                                                                                             
/* Component EO Basic Libraries */
#define COMP_EO_BASICLIB_OSAL   CL_TRUE
#define COMP_EO_BASICLIB_TIMER   CL_TRUE
#define COMP_EO_BASICLIB_BUFFER   CL_TRUE
#define COMP_EO_BASICLIB_IOC   CL_TRUE
#define COMP_EO_BASICLIB_RMD   CL_TRUE
#define COMP_EO_BASICLIB_EO   CL_TRUE
#define COMP_EO_BASICLIB_OM   ${omLibEnable}
#define COMP_EO_BASICLIB_HAL  ${halLibEnable}
#define COMP_EO_BASICLIB_DBAL  ${dbalLibEnable}
                                                                                                                             
/* Component EO Client Libraries */                                                                                                                            

#define COMP_EO_CLIENTLIB_COR   ${corClLib}
#define COMP_EO_CLIENTLIB_CM    ${cmClLib}                  
#define COMP_EO_CLIENTLIB_NAME    ${nameClLib}                  
#define COMP_EO_CLIENTLIB_LOG    ${logClLib}                  
#define COMP_EO_CLIENTLIB_TRACE    CL_FALSE                 
#define COMP_EO_CLIENTLIB_DIAG    CL_FALSE
#define COMP_EO_CLIENTLIB_TXN    ${txnClLib}
#define COMP_EO_CLIENTLIB_NA    CL_FALSE
#define COMP_EO_CLIENTLIB_PROV    ${provLib}
#define COMP_EO_CLIENTLIB_ALARM    ${alarmClLib}
#define COMP_EO_CLIENTLIB_DEBUG    ${debugClLib}
#define COMP_EO_CLIENTLIB_GMS    CL_FALSE
                                                                                                                             
#endif

""")

compMakefileTemplate = Template("""
################################################################################
#
# This Makefile is auto-generated by ClovisWorks
#
# Makefile for ${exeName}
#
# This Makefile assumes the following:
#	- CLOVIS_ROOT environment variable is specified properly
#	- Entire source tree under $(CLOVIS_ROOT)/ASP is checked out
#
# 
# Date: ${DateTime}
# User: ${User} 
# 
#
################################################################################

# Component name (using all lowercase):

EXENAME	:= ${exeName}

# List local source files needed for the component server:

SRC_FILES	:= $(wildcard *.c)

# List other ASP components of which client libraries your component
# depends on:

DEP_COMP_LIST	:= utils osal timer buffer ioc rmd eo amf event ckpt dbal debug cor prov alarm om hal name txn idl
# FIXME: Indirect dependencies via client library needs need to be
# added by hand for now:
DEP_COMP_LIST	+= cnt

# List ASP libraries needed to get this server built (or None):

ASP_LIBS	:= libClTimer.a  libClBuffer.a  libClOsal.a  libClCnt.a  ${omClientLib} libClHal.a  libClCorClient.a  libClEo.a  ${cmClientLib} ${provClientLib} ${alarmClientLib} \
		   libClIoc.a libClRmd.a libClUtils.a libClAmfClient.a libClDbal.a libClGDBM.so libClCkpt.a libClEventClient.a libClTxnAgent.a  libClLogClient.a libClIdl.a\
		   libClDebugClient.a libClNameClient.a ${idlLib}
                   
# List any third party libs needed to get this server built (or None):
THIRD_PARTY_EZXML_PATH = $(CLOVIS_ROOT)/ASP/3rdparty/ezxml/stable                                                                                                                                                                                    
                                                                                                                                                                                    
EXTRA_CPPFLAGS  := -I$(THIRD_PARTY_EZXML_PATH)


# List any system libraries needed to get this server built (or None):

SYS_LIBS	:= -lpthread -lgdbm -ldl

# Executable name (when building server exectuable):
# Notice the '=' in the assignment.

EXE_NAME	= $(EXENAME)

CPPFLAGS   += -I$(ASP_CONFIG)

include $(CLOVIS_ROOT)/ASP/mk/make-server.mk
""")


appMakeFileTemplate = Template("""

################################################################################
#
# 
# This Makefile is auto-generated by ClovisWorks
# Makefile for components
#
# This Makefile assumes the following:
#       - CLOVIS_ROOT environment variable is specified properly
#       - Entire source tree under $(CLOVIS_ROOT)/ASP is checked out
#
# Date: ${DateTime}
# User: ${User} 
#
################################################################################
                                                                                                                                                                                    
# Subdirectories having Makefiles and need recursive escalation:
# common should always be before client and server
                                                                                                                                                                                    
SUBDIRS          = ${idlSubDir} ${compList}
                                                                                                                                                                                    
#
# If you have any ordering dependence among subdirectories, list them as
# target-prerequisite pairs.
#
                                                                                                                                                                                    
include $(CLOVIS_ROOT)/ASP/mk/make-subdir.mk

""")

#------------------------------------------------------------------------------
def processComponent(cmpList):

	global idlFile
	global globalEOMap
	idlExists = 0
	eoList = []
       	if os.path.exists(idlFile):       	    
		idlDoc  = xml.dom.minidom.parse(idlFile)
		eoList = idlDoc.getElementsByTagName("EO")
		idlExists = 1
	symbolMap = dict()
	for cmp in cmpList:
		cpmName = cmp.attributes["Name"].value
		cpmName = string.replace(cpmName, " ", "_")
		cpmName = string.replace(cpmName, "-", "_")
		symbolMap["cpmName"] = cpmName
		eo = cmp.getElementsByTagName("EOProperties")[0]
		symbolMap["eoName"]        = eo.attributes["eoname"].value
		symbolMap["eoThreadPri"]   = eo.attributes["threadpriority"].value
		eoThreadCount = int(eo.attributes["threadcount"].value)
		#Mininum Thread Count should be 2.
		if eoThreadCount < 2:
		    eoThreadCount = 2
		symbolMap["eoNumThread"]   = eoThreadCount
		symbolMap["iocPort"]       = eo.attributes["iocportnumber"].value
		symbolMap["threadPolicy"]  = eo.attributes["mainthreadusagepolicy"].value
		symbolMap["eoName"]  = eo.attributes["eoname"].value
		symbolMap["maxNoClients"]  = eo.attributes["maxNoClients"].value
		eoThreadPriority = eo.attributes["threadpriority"].value
		if eoThreadPriority == "PRIORITY_LOW":
			eoThreadPriority = "CL_OSAL_THREAD_PRI_LOW"
		if eoThreadPriority == "PRIORITY_MEDIUM":
			eoThreadPriority = "CL_OSAL_THREAD_PRI_MEDIUM"
		if eoThreadPriority == "PRIORITY_HIGH":
			eoThreadPriority = "CL_OSAL_THREAD_PRI_HIGH"		
		symbolMap["eoThreadPriority"] = eoThreadPriority
			
		libObj = eo.getElementsByTagName("basiclib")[0]
		cliObj = eo.getElementsByTagName("eoclientlib")[0]

		symbolMap["omLibEnable"]   = libObj.attributes["OM"].value
		symbolMap["halLibEnable"]  = libObj.attributes["HAL"].value
		symbolMap["dbalLibEnable"] = libObj.attributes["DBAL"].value

		symbolMap["corClLib"]      = cliObj.attributes["COR"].value
		symbolMap["cmClLib"]       = cliObj.attributes["CM"].value
		symbolMap["nameClLib"]     = cliObj.attributes["NameService"].value
		symbolMap["logClLib"]      = cliObj.attributes["LOG"].value
		symbolMap["traceClLib"]    = cliObj.attributes["Trace"].value
		symbolMap["diagClLib"]     = cliObj.attributes["Diagnostics"].value
		symbolMap["txnClLib"]      = cliObj.attributes["Transaction"].value        
		symbolMap["provLib"]      = cliObj.attributes["Prov"].value
		symbolMap["alarmClLib"]    = cliObj.attributes["Alarm"].value
		symbolMap["debugClLib"]    = cliObj.attributes["Debug"].value        

		symbolMap["hasEOServices"] = 0
		globalEOMap[cpmName] = 0
		if idlExists == 1:
			for eo in eoList:
				eoName = symbolMap["eoName"]
				if eo.attributes["name"].value == symbolMap["eoName"]:
					serviceList = eo.getElementsByTagName("Service")
					if len(serviceList) > 0:
						symbolMap["hasEOServices"] = 1
						globalEOMap[cpmName] = eoName
				
		result = clConfigHeaderFileTemplate.safe_substitute(symbolMap, DateTime=date, User=user)
		if os.path.exists(cpmName) == False:       	    
			os.mkdir(cpmName)   
		    
		file = cpmName + "/" + "clCompCfg.h"     
		fd = open(file , "w")
		fd.write(result)
		fd.close()
		destApphFile = cpmName + "/" + templateApphFile
		destAppCFile = cpmName + "/" + templateAppCFile
		if (codeGenMode == "true") or not (os.path.isfile(destApphFile)):
			shutil.copyfile(templateApphFilePath, destApphFile)
		if (codeGenMode == "true") or not (os.path.isfile(destAppCFile)):
			shutil.copyfile(templateAppCFilePath, destAppCFile)
#------------------------------------------------------------------------------
#------------------------------------------------------------------------------
#Script Execution Starts Here.
date = unicode(time.strftime("%D at %H:%M:%S", time.localtime()))
user = getpass.getuser()

templatedir = sys.argv[2] 
codeGenMode = sys.argv[3]
idlFile = sys.argv[4]
globalEOMap = dict()

templateApphFile="clCompAppMain.h"
templateAppCFile="clCompAppMain.c"
templateApphFilePath=templatedir + "/" + "clCompAppMain.h"
templateAppCFilePath=templatedir + "/" + "clCompAppMain.c"

componentXml  = sys.argv[1]
componentDoc  = xml.dom.minidom.parse(componentXml)
componentList = componentDoc.getElementsByTagName("component:SAFComponent");
processComponent(componentList)
#Generate Makefile for App
compList = ""
appMakefile = open("Makefile", "w")
for component in componentList:
	cpmName = component.attributes["Name"].value
	compList += cpmName + " "

idlExists=0
#------------------------------------------------------------------------------

#Generate Makefile for each Component 
for component in componentList:
	cpmName = component.attributes["Name"].value
	map = dict()
	map["DateTime"]=date
	map["User"]=user
	map["compName"] = cpmName
	imageName = component.attributes["InstantiationCMD"].value
	if imageName == None or imageName == "":
		imageName = "asp_" + cpmName
	map["exeName"] = imageName
	map["cmClientLib"] = ""
	map["alarmClientLib"] = ""
	map["omClientLib"] = ""
	map["provClientLib"] = ""
	eo = component.getElementsByTagName("EOProperties")[0]
	cliObj = eo.getElementsByTagName("eoclientlib")[0]
	
	if cliObj.attributes["CM"].value == "CL_TRUE":
		map["cmClientLib"] = "libClCm.a"
		
	if cliObj.attributes["Alarm"].value == "CL_TRUE":
		map["alarmClientLib"] = "libClAlarmClient.a"

	if cliObj.attributes["Prov"].value == "CL_TRUE":
		map["provClientLib"] = "libClProv.a"

	basicLibObj = eo.getElementsByTagName("basiclib")[0]
	if basicLibObj.attributes["OM"].value == "CL_TRUE":
		map["omClientLib"] = "libClOmClient.a"

	map["idlLib"] = ""
	if globalEOMap[cpmName] != 0:
		idlExists = 1
		map["idlLib"] = "libCl" + globalEOMap[cpmName] + "Server.a"

	file = cpmName + "/Makefile" 	
	compMakefile = open(file, "w") 
	compMakefile.write(compMakefileTemplate.safe_substitute(map))
	compMakefile.close()

idlSubDir = ""
if idlExists == 1:
	idlSubDir = "idl"
appMakefile.write(appMakeFileTemplate.safe_substitute(compList = compList, DateTime = date, User = user, idlSubDir = idlSubDir))
appMakefile.close()
	