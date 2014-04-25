/* 
 * File PhysAddress.cxx
 * This file has been auto-generated by Y2CPP, the
 * plug-in of pyang.
 */ 

#include <iostream>
#include <string>
#include "PhysAddress.hxx"


namespace ietfYangTypes {

    PhysAddress::PhysAddress()
    {
    };

    std::string PhysAddress::getValue()
    {
        return this->Value;
    };

    void PhysAddress::setValue(std::string value)
    {
        this->Value = value;
    };

    ietfYangTypes::PhysAddress& PhysAddress::operator=(const ietfYangTypes::PhysAddress& physAddress)
    {
        Value = physAddress.Value;
        return *this;
    };

    PhysAddress::~PhysAddress()
    {
    };

    std::ostream& operator<<(std::ostream& os, const ietfYangTypes::PhysAddress& physAddress)
    {
        return os << physAddress.Value;
    };

    std::istream& operator>>(std::istream& is, ietfYangTypes::PhysAddress& physAddress)
    {
        return is >> physAddress.Value;
    };

}
/* namespace ietfYangTypes */
