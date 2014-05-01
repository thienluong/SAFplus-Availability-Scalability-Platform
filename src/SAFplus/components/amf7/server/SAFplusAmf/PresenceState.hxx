/* 
 * File PresenceState.hxx
 * This file has been auto-generated by Y2CPP, the
 * plug-in of pyang.
 */ 

#pragma once
#ifndef PRESENCESTATE_HXX_
#define PRESENCESTATE_HXX_
#include "SAFplusAmfCommon.hxx"

#include "MgtEnumType.hxx"
#include <iostream>

namespace SAFplusAmf
  {

    enum class PresenceState
  {
        uninstantiated, instantiating, instantiated, terminating, restarting, instantiationFailed, terminationFailed
      };
    std::ostream& operator<<(std::ostream& os, const PresenceState& e);
    std::istream& operator>>(std::istream& is, PresenceState& e);

    /*
     * This is the class that will handle the conversion for us.
     */
    class PresenceStateManager : public SAFplus::MgtEnumType<PresenceStateManager, PresenceState> {
        PresenceStateManager();  // private to prevent instantiation
    public:
        static const vec_t en2str_vec;  // This is the lookup table.
    };
}
/* namespace SAFplusAmf */
#endif /* PRESENCESTATE_HXX_ */
