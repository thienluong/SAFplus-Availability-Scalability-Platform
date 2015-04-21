/* 
 * File Timeticks.cxx
 * This file has been auto-generated by Y2CPP, the
 * plug-in of pyang.
 */ 
#include "ietfYangTypesCommon.hxx"

#include <iostream>
#include "clTransaction.hxx"
#include "Timeticks.hxx"


namespace ietfYangTypes
  {

    Timeticks::Timeticks()
    {
    };

    unsigned int Timeticks::getValue()
    {
        return this->value;
    };

    void Timeticks::setValue(unsigned int value, SAFplus::Transaction &t)
    {
        if(&t == &SAFplus::NO_TXN) this->value = value;
        else
        {
            SAFplus::SimpleTxnOperation<unsigned int> *opt = new SAFplus::SimpleTxnOperation<unsigned int>(&this->value,value);
            t.addOperation(opt);
        }
    };

    ietfYangTypes::Timeticks& Timeticks::operator=(const ietfYangTypes::Timeticks &timeticks)
    {
        value = timeticks.value;
        return *this;
    };

    Timeticks::~Timeticks()
    {
    };

    std::ostream& operator<<(std::ostream &os, const ietfYangTypes::Timeticks &timeticks)
    {
        return os << timeticks.value;
    };

    std::istream& operator>>(std::istream &is, ietfYangTypes::Timeticks &timeticks)
    {
        return is >> timeticks.value;
    };

}
/* namespace ietfYangTypes */