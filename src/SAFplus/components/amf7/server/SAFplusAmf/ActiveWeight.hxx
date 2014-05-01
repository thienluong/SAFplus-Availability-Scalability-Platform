/* 
 * File ActiveWeight.hxx
 * This file has been auto-generated by Y2CPP, the
 * plug-in of pyang.
 */ 

#pragma once
#ifndef ACTIVEWEIGHT_HXX_
#define ACTIVEWEIGHT_HXX_
#include "SAFplusAmfCommon.hxx"

#include "clMgtObject.hxx"
#include "clMgtProv.hxx"
#include <vector>
#include "MgtFactory.hxx"
#include <string>

namespace SAFplusAmf
  {

    class ActiveWeight : public ClMgtObject {

        /* Apply MGT object factory */
        REGISTER(ActiveWeight);

    public:
        ClMgtProv<std::string> resource;
        ClMgtProv<long int> value;

    public:
        ActiveWeight();
        ActiveWeight(std::string resourceValue);
        std::vector<std::string> getKeys();
        std::vector<std::string>* getChildNames();

        /*
         * XPATH: /SAFplusAmf/ServiceInstance/activeWeight/resource
         */
        std::string getResource();

        /*
         * XPATH: /SAFplusAmf/ServiceInstance/activeWeight/resource
         */
        void setResource(std::string resourceValue);

        /*
         * XPATH: /SAFplusAmf/ServiceInstance/activeWeight/value
         */
        long int getValue();

        /*
         * XPATH: /SAFplusAmf/ServiceInstance/activeWeight/value
         */
        void setValue(long int valueValue);
        ~ActiveWeight();

    };
}
/* namespace SAFplusAmf */
#endif /* ACTIVEWEIGHT_HXX_ */
