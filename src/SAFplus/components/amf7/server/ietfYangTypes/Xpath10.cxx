/* 
 * File Xpath10.cxx
 * This file has been auto-generated by Y2CPP, the
 * plug-in of pyang.
 */ 

#include <iostream>
#include <string>
#include "Xpath10.hxx"


namespace ietfYangTypes {

    Xpath10::Xpath10()
    {
    };

    std::string Xpath10::getValue()
    {
        return this->Value;
    };

    void Xpath10::setValue(std::string value)
    {
        this->Value = value;
    };

    ietfYangTypes::Xpath10& Xpath10::operator=(const ietfYangTypes::Xpath10& xpath10)
    {
        Value = xpath10.Value;
        return *this;
    };

    Xpath10::~Xpath10()
    {
    };

    std::ostream& operator<<(std::ostream& os, const ietfYangTypes::Xpath10& xpath10)
    {
        return os << xpath10.Value;
    };

    std::istream& operator>>(std::istream& is, ietfYangTypes::Xpath10& xpath10)
    {
        return is >> xpath10.Value;
    };

}
/* namespace ietfYangTypes */