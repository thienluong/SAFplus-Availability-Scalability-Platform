/* 
 * File Timeticks.hxx
 * This file has been auto-generated by Y2CPP, the
 * plug-in of pyang.
 */ 

#pragma once
#ifndef TIMETICKS_HXX_
#define TIMETICKS_HXX_
#include "ietfYangTypesCommon.hxx"

#include <iostream>

namespace ietfYangTypes
  {

    class Timeticks {
    public:
        unsigned int Value;

    public:
        Timeticks();
        unsigned int getValue();
        void setValue(unsigned int value);
        ietfYangTypes::Timeticks& operator=(const ietfYangTypes::Timeticks &timeticks);
        friend std::ostream& operator<<(std::ostream &os, const ietfYangTypes::Timeticks &timeticks);
        friend std::istream& operator>>(std::istream &is, ietfYangTypes::Timeticks &timeticks);
        ~Timeticks();

    };
}
/* namespace ietfYangTypes */
#endif /* TIMETICKS_HXX_ */
