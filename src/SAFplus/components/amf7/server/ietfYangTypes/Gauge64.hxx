/* 
 * File Gauge64.hxx
 * This file has been auto-generated by Y2CPP, the
 * plug-in of pyang.
 */ 

#pragma once
#ifndef GAUGE64_HXX_
#define GAUGE64_HXX_
#include "ietfYangTypesCommon.hxx"

#include <iostream>

namespace ietfYangTypes
  {

    class Gauge64 {
    public:
        unsigned long int Value;

    public:
        Gauge64();
        unsigned long int getValue();
        void setValue(unsigned long int value);
        ietfYangTypes::Gauge64& operator=(const ietfYangTypes::Gauge64 &gauge64);
        friend std::ostream& operator<<(std::ostream &os, const ietfYangTypes::Gauge64 &gauge64);
        friend std::istream& operator>>(std::istream &is, ietfYangTypes::Gauge64 &gauge64);
        ~Gauge64();

    };
}
/* namespace ietfYangTypes */
#endif /* GAUGE64_HXX_ */
