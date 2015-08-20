/* 
 * File ObjectIdentifier.cxx
 * This file has been auto-generated by Y2CPP, the
 * plug-in of pyang.
 */ 
#include "ietfYangTypesCommon.hxx"

#include <iostream>
#include <string>
#include "clTransaction.hxx"
#include "ObjectIdentifier.hxx"


namespace ietfYangTypes
  {

    ObjectIdentifier::ObjectIdentifier()
    {
    };

    std::string ObjectIdentifier::getValue()
    {
        return this->value;
    };

    void ObjectIdentifier::setValue(std::string value, SAFplus::Transaction &t)
    {
        if(&t == &SAFplus::NO_TXN) this->value = value;
        else
        {
            SAFplus::SimpleTxnOperation<std::string> *opt = new SAFplus::SimpleTxnOperation<std::string>(&this->value,value);
            t.addOperation(opt);
        }
    };

    ::ietfYangTypes::ObjectIdentifier& ObjectIdentifier::operator=(const ::ietfYangTypes::ObjectIdentifier &objectIdentifier)
    {
        value = objectIdentifier.value;
        return *this;
    };

    ObjectIdentifier::~ObjectIdentifier()
    {
    };

    std::ostream& operator<<(std::ostream &os, const ::ietfYangTypes::ObjectIdentifier &objectIdentifier)
    {
        return os << objectIdentifier.value;
    };

    std::istream& operator>>(std::istream &is, ::ietfYangTypes::ObjectIdentifier &objectIdentifier)
    {
        return is >> objectIdentifier.value;
    };

}
/* namespace ::ietfYangTypes */