/* 
 * File FaultState.hxx
 * This file has been auto-generated by Y2CPP, the
 * plug-in of pyang.
 */ 

#pragma once
#ifndef FAULTSTATE_HXX_
#define FAULTSTATE_HXX_

#include "FaultEnumsCommon.hxx"
#include <iostream>
#include "MgtEnumType.hxx"

namespace FaultEnums
  {

    enum class FaultState
      {
        STATE_UNDEFINED, STATE_UP, STATE_DOWN
      };
    std::ostream& operator<<(std::ostream& os, const FaultState& e);
    std::istream& operator>>(std::istream& is, FaultState& e);
    const char* c_str(const FaultState& e);

    /*
     * This is the class that will handle the conversion for us.
     */
    class FaultStateManager : public SAFplus::MgtEnumType<FaultStateManager, FaultState> {
        FaultStateManager();  // private to prevent instantiation
    public:
        static const map_t en2str_map;  // This is the lookup table.
    };
}
/* namespace ::FaultEnums */
#endif /* FAULTSTATE_HXX_ */
