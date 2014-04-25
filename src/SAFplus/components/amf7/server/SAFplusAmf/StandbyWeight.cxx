/* 
 * File StandbyWeight.cxx
 * This file has been auto-generated by Y2CPP, the
 * plug-in of pyang.
 */ 

#include "clMgtObject.hxx"
#include "clMgtProv.hxx"
#include <vector>
#include "MgtFactory.hxx"
#include <string>
#include "StandbyWeight.hxx"


namespace SAFplusAmf {

    /* Apply MGT object factory */
    REGISTERIMPL(StandbyWeight, /SAFplusAmf/ServiceInstance/standbyWeight)

    StandbyWeight::StandbyWeight(): ClMgtObject("standbyWeight"), resource("resource"), value("value")
    {
        this->addChildObject(&resource, "resource");
        this->addChildObject(&value, "value");
        this->addKey("resource");
    };

    StandbyWeight::StandbyWeight(std::string resourceValue): ClMgtObject("standbyWeight"), resource("resource"), value("value")
    {
        this->resource.Value =  resourceValue;
        this->addKey("resource");
        this->addChildObject(&resource, "resource");
        this->addChildObject(&value, "value");
    };

    std::vector<std::string> StandbyWeight::getKeys()
    {
        std::string keyNames[] = { "resource" };
        return std::vector<std::string> (keyNames, keyNames + sizeof(keyNames) / sizeof(keyNames[0]));
    };

    std::vector<std::string>* StandbyWeight::getChildNames()
    {
        std::string childNames[] = { "resource", "value" };
        return new std::vector<std::string> (childNames, childNames + sizeof(childNames) / sizeof(childNames[0]));
    };

    /*
     * XPATH: /SAFplusAmf/ServiceInstance/standbyWeight/resource
     */
    std::string StandbyWeight::getResource()
    {
        return this->resource.Value;
    };

    /*
     * XPATH: /SAFplusAmf/ServiceInstance/standbyWeight/resource
     */
    void StandbyWeight::setResource(std::string resourceValue)
    {
        this->resource.Value = resourceValue;
    };

    /*
     * XPATH: /SAFplusAmf/ServiceInstance/standbyWeight/value
     */
    long int StandbyWeight::getValue()
    {
        return this->value.Value;
    };

    /*
     * XPATH: /SAFplusAmf/ServiceInstance/standbyWeight/value
     */
    void StandbyWeight::setValue(long int valueValue)
    {
        this->value.Value = valueValue;
    };

    StandbyWeight::~StandbyWeight()
    {
    };

}
/* namespace SAFplusAmf */