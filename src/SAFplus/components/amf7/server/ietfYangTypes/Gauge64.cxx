/* 
 * File Gauge64.cxx
 * This file has been auto-generated by Y2CPP, the
 * plug-in of pyang.
 */ 
#include "ietfYangTypesCommon.hxx"

#include <iostream>
#include "Gauge64.hxx"


namespace ietfYangTypes
  {

    Gauge64::Gauge64()
    {
    };

    unsigned long int Gauge64::getValue()
    {
        return this->Value;
    };

    void Gauge64::setValue(unsigned long int value)
    {
        this->Value = value;
    };

    ietfYangTypes::Gauge64& Gauge64::operator=(const ietfYangTypes::Gauge64 &gauge64)
    {
        Value = gauge64.Value;
        return *this;
    };

    Gauge64::~Gauge64()
    {
    };

    std::ostream& operator<<(std::ostream &os, const ietfYangTypes::Gauge64 &gauge64)
    {
        return os << gauge64.Value;
    };

    std::istream& operator>>(std::istream &is, ietfYangTypes::Gauge64 &gauge64)
    {
        return is >> gauge64.Value;
    };

}
/* namespace ietfYangTypes */
