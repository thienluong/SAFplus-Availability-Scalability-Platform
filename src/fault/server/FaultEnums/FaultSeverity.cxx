/* 
 * File FaultSeverity.cxx
 * This file has been auto-generated by Y2CPP, the
 * plug-in of pyang.
 */ 

#include "FaultEnumsCommon.hxx"
#include <iostream>
#include "MgtEnumType.hxx"
#include "FaultSeverity.hxx"


namespace FaultEnums
  {

    /*
     * Provide an implementation of the en2str_map lookup table.
     */
    const FaultSeverityManager::map_t FaultSeverityManager::en2str_map = {
            pair_t(FaultSeverity::ALARM_SEVERITY_INVALID, "ALARM_SEVERITY_INVALID"),
            pair_t(FaultSeverity::ALARM_SEVERITY_CRITICAL, "ALARM_SEVERITY_CRITICAL"),
            pair_t(FaultSeverity::ALARM_SEVERITY_MAJOR, "ALARM_SEVERITY_MAJOR"),
            pair_t(FaultSeverity::ALARM_SEVERITY_MINOR, "ALARM_SEVERITY_MINOR"),
            pair_t(FaultSeverity::ALARM_SEVERITY_WARNING, "ALARM_SEVERITY_WARNING"),
            pair_t(FaultSeverity::ALARM_SEVERITY_INDETERMINATE, "ALARM_SEVERITY_INDETERMINATE"),
            pair_t(FaultSeverity::ALARM_SEVERITY_CLEAR, "ALARM_SEVERITY_CLEAR"),
            pair_t(FaultSeverity::ALARM_SEVERITY_COUNT, "ALARM_SEVERITY_COUNT")
    }; // uses c++11 initializer lists 

    const char* c_str(const ::FaultEnums::FaultSeverity &faultSeverity)
    {
        return FaultSeverityManager::c_str(faultSeverity);
    };

    std::ostream& operator<<(std::ostream &os, const ::FaultEnums::FaultSeverity &faultSeverity)
    {
        return os << FaultSeverityManager::toString(faultSeverity);
    };

    std::istream& operator>>(std::istream &is, ::FaultEnums::FaultSeverity &faultSeverity)
    {
        std::string buf;
        is >> buf;
        faultSeverity = FaultSeverityManager::toEnum(buf);
        return is;
    };

}
/* namespace ::FaultEnums */
