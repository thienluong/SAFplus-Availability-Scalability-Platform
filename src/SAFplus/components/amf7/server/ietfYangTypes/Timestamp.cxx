/* 
 * File Timestamp.cxx
 * This file has been auto-generated by Y2CPP, the
 * plug-in of pyang.
 */ 
#include "ietfYangTypesCommon.hxx"

#include <iostream>
#include "Timestamp.hxx"


namespace ietfYangTypes
  {

    Timestamp::Timestamp()
    {
    };

    unsigned int Timestamp::getValue()
    {
        return this->Value;
    };

    void Timestamp::setValue(unsigned int value)
    {
        this->Value = value;
    };

    ietfYangTypes::Timestamp& Timestamp::operator=(const ietfYangTypes::Timestamp &timestamp)
    {
        Value = timestamp.Value;
        return *this;
    };

    Timestamp::~Timestamp()
    {
    };

    std::ostream& operator<<(std::ostream &os, const ietfYangTypes::Timestamp &timestamp)
    {
        return os << timestamp.Value;
    };

    std::istream& operator>>(std::istream &is, ietfYangTypes::Timestamp &timestamp)
    {
        return is >> timestamp.Value;
    };

}
/* namespace ietfYangTypes */
