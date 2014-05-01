/* 
 * File MacAddress.cxx
 * This file has been auto-generated by Y2CPP, the
 * plug-in of pyang.
 */ 
#include "ietfYangTypesCommon.hxx"

#include <iostream>
#include <string>
#include "MacAddress.hxx"


namespace ietfYangTypes
  {

    MacAddress::MacAddress()
    {
    };

    std::string MacAddress::getValue()
    {
        return this->Value;
    };

    void MacAddress::setValue(std::string value)
    {
        this->Value = value;
    };

    ietfYangTypes::MacAddress& MacAddress::operator=(const ietfYangTypes::MacAddress &macAddress)
    {
        Value = macAddress.Value;
        return *this;
    };

    MacAddress::~MacAddress()
    {
    };

    std::ostream& operator<<(std::ostream &os, const ietfYangTypes::MacAddress &macAddress)
    {
        return os << macAddress.Value;
    };

    std::istream& operator>>(std::istream &is, ietfYangTypes::MacAddress &macAddress)
    {
        return is >> macAddress.Value;
    };

}
/* namespace ietfYangTypes */
