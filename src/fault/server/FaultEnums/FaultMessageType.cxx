/* 
 * File FaultMessageType.cxx
 * This file has been auto-generated by Y2CPP, the
 * plug-in of pyang.
 */ 

#include "FaultEnumsCommon.hxx"
#include <iostream>
#include "MgtEnumType.hxx"
#include "FaultMessageType.hxx"


namespace FaultEnums
  {

    /*
     * Provide an implementation of the en2str_map lookup table.
     */
    const FaultMessageTypeManager::map_t FaultMessageTypeManager::en2str_map = {
            pair_t(FaultMessageType::MSG_UNDEFINED, "MSG_UNDEFINED"),
            pair_t(FaultMessageType::MSG_ENTITY_JOIN, "MSG_ENTITY_JOIN"),
            pair_t(FaultMessageType::MSG_ENTITY_LEAVE, "MSG_ENTITY_LEAVE"),
            pair_t(FaultMessageType::MSG_ENTITY_FAULT, "MSG_ENTITY_FAULT"),
            pair_t(FaultMessageType::MSG_ENTITY_STATE_CHANGE, "MSG_ENTITY_STATE_CHANGE"),
            pair_t(FaultMessageType::MSG_ENTITY_JOIN_BROADCAST, "MSG_ENTITY_JOIN_BROADCAST"),
            pair_t(FaultMessageType::MSG_ENTITY_LEAVE_BROADCAST, "MSG_ENTITY_LEAVE_BROADCAST"),
            pair_t(FaultMessageType::MSG_ENTITY_FAULT_BROADCAST, "MSG_ENTITY_FAULT_BROADCAST"),
            pair_t(FaultMessageType::MSG_ENTITY_STATE_CHANGE_BROADCAST, "MSG_ENTITY_STATE_CHANGE_BROADCAST"),
            pair_t(FaultMessageType::MSG_ENTITY_COUNT, "MSG_ENTITY_COUNT")
    }; // uses c++11 initializer lists 

    const char* c_str(const ::FaultEnums::FaultMessageType &faultMessageType)
    {
        return FaultMessageTypeManager::c_str(faultMessageType);
    };

    std::ostream& operator<<(std::ostream &os, const ::FaultEnums::FaultMessageType &faultMessageType)
    {
        return os << FaultMessageTypeManager::toString(faultMessageType);
    };

    std::istream& operator>>(std::istream &is, ::FaultEnums::FaultMessageType &faultMessageType)
    {
        std::string buf;
        is >> buf;
        faultMessageType = FaultMessageTypeManager::toEnum(buf);
        return is;
    };

}
/* namespace ::FaultEnums */
