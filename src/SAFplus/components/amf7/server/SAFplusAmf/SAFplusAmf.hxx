/* 
 * File SAFplusAmf.hxx
 * This file has been auto-generated by Y2CPP, the
 * plug-in of pyang.
 */ 

#pragma once
#ifndef SAFPLUSAMFROOT_HXX_
#define SAFPLUSAMFROOT_HXX_
#include "SAFplusAmfCommon.hxx"

#include "clMgtList.hxx"
#include <vector>
#include "MgtFactory.hxx"
#include "clMgtObject.hxx"
#include "clMgtProv.hxx"
#include "SaTimeT.hxx"

namespace SAFplusAmf
  {

    class SAFplusAmfRoot : public ClMgtObject {

        /* Apply MGT object factory */
        REGISTER(SAFplusAmfRoot);

    public:

        /*
         * This attribute indicates the interval at which the corresponding healthcheck should be initiated (in milliseconds).
         */
        ClMgtProv<SAFplusTypes::SaTimeT> healthCheckPeriod;

        /*
         * This attribute indicates the maximum time allowable for components to not reply to the health check (in milliseconds).  After this time passes with no response from the component, it will be faulted
         */
        ClMgtProv<SAFplusTypes::SaTimeT> healthCheckMaxSilence;

        /*
         * 
         */
        ClMgtList clusterList;
        ClMgtList nodeList;

        /*
         * A Service Group is a Service Availability Forum defined concept that corresponds to a group of redundant processes that should fail over as a unit.
         */
        ClMgtList serviceGroupList;

        /*
         * 
         */
        ClMgtList componentList;

        /*
         * 
         */
        ClMgtList componentServiceInstanceList;

        /*
         * 
         */
        ClMgtList serviceInstanceList;

        /*
         * 
         */
        ClMgtList serviceUnitList;

        /*
         * 
         */
        ClMgtList applicationList;

        /*
         * Look up any entity by its string name
         */
        ClMgtList entityByNameList;

        /*
         * Look up any entity by its identifier
         */
        ClMgtList entityByIdList;

    public:
        SAFplusAmfRoot();
        std::vector<std::string>* getChildNames();

        /*
         * XPATH: /SAFplusAmf/healthCheckPeriod
         */
        SAFplusTypes::SaTimeT getHealthCheckPeriod();

        /*
         * XPATH: /SAFplusAmf/healthCheckPeriod
         */
        void setHealthCheckPeriod(SAFplusTypes::SaTimeT healthCheckPeriodValue);

        /*
         * XPATH: /SAFplusAmf/healthCheckMaxSilence
         */
        SAFplusTypes::SaTimeT getHealthCheckMaxSilence();

        /*
         * XPATH: /SAFplusAmf/healthCheckMaxSilence
         */
        void setHealthCheckMaxSilence(SAFplusTypes::SaTimeT healthCheckMaxSilenceValue);
        void load(ClMgtDatabase *db);
        ~SAFplusAmfRoot();

    };
}
/* namespace SAFplusAmf */
#endif /* SAFPLUSAMFROOT_HXX_ */
