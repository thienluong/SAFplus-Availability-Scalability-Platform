/* 
 * File Sensor.hxx
 * This file has been auto-generated by Y2CPP, the
 * plug-in of pyang.
 */ 

#pragma once
#ifndef SENSOR_HXX_
#define SENSOR_HXX_
#include "SAFplusTypesCommon.hxx"

#include "Val.hxx"
#include <vector>
#include "clMgtObject.hxx"
#include "Val.hxx"
#include "clMgtProv.hxx"
#include <string>

namespace SAFplusTypes
  {

    class Sensor : public SAFplus::ClMgtObject {
    public:
        SAFplus::ClMgtProv<std::string> name;
        SAFplus::ClMgtProv<std::string> desc;

    public:
        Sensor();
        std::vector<std::string>* getChildNames();

        /*
         * XPATH: /SAFplusTypes/sensor/name
         */
        std::string getName();

        /*
         * XPATH: /SAFplusTypes/sensor/name
         */
        void setName(std::string nameValue);

        /*
         * XPATH: /SAFplusTypes/sensor/desc
         */
        std::string getDesc();

        /*
         * XPATH: /SAFplusTypes/sensor/desc
         */
        void setDesc(std::string descValue);

        /*
         * XPATH: /SAFplusTypes/sensor/val
         */
        SAFplusTypes::Val* getVal();

        /*
         * XPATH: /SAFplusTypes/sensor/val
         */
        void addVal(SAFplusTypes::Val *valValue);
        ~Sensor();

    };
}
/* namespace SAFplusTypes */
#endif /* SENSOR_HXX_ */
