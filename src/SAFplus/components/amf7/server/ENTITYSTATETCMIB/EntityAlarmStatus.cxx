/* 
 * File EntityAlarmStatus.cxx
 * This file has been auto-generated by Y2CPP, the
 * plug-in of pyang.
 */ 

#include <iostream>
#include <bitset>
#include "EntityAlarmStatus.hxx"


namespace ENTITYSTATETCMIB {

    EntityAlarmStatus::EntityAlarmStatus()
    {
    };

    std::bitset<7> EntityAlarmStatus::getValue()
    {
        return this->Value;
    };

    void EntityAlarmStatus::setValue(std::bitset<7> value)
    {
        this->Value = value;
    };

    ENTITYSTATETCMIB::EntityAlarmStatus& EntityAlarmStatus::operator=(const ENTITYSTATETCMIB::EntityAlarmStatus &EntityAlarmStatus)
    {
        Value = EntityAlarmStatus.Value;
        return *this;
    };

    EntityAlarmStatus::~EntityAlarmStatus()
    {
    };

    std::ostream& operator<<(std::ostream &os, const ENTITYSTATETCMIB::EntityAlarmStatus &EntityAlarmStatus)
    {
        return os << EntityAlarmStatus.Value;
    };

    std::istream& operator>>(std::istream &is, ENTITYSTATETCMIB::EntityAlarmStatus &EntityAlarmStatus)
    {
        return is >> EntityAlarmStatus.Value;
    };

}
/* namespace ENTITYSTATETCMIB */
