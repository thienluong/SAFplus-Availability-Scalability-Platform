/* 
 * File HighAvailabilityState.cxx
 * This file has been auto-generated by Y2CPP, the
 * plug-in of pyang.
 */ 

#include "MgtEnumType.hxx"
#include <iostream>
#include "HighAvailabilityState.hxx"


namespace SAFplusAmf {

    /*
     * Provide an implementation of the en2str_vec lookup table.
     */
    const HighAvailabilityStateManager::vec_t HighAvailabilityStateManager::en2str_vec = {
            pair_t(HighAvailabilityState::active, "active"),
            pair_t(HighAvailabilityState::standby, "standby"),
            pair_t(HighAvailabilityState::quiescing, "quiescing"),
            pair_t(HighAvailabilityState::idle, "idle")
    }; // uses c++11 initializer lists 

    std::ostream& operator<<(std::ostream& os, const SAFplusAmf::HighAvailabilityState& highAvailabilityState)
    {
        return os << HighAvailabilityStateManager::toString(highAvailabilityState);
    };

    std::istream& operator>>(std::istream& is, SAFplusAmf::HighAvailabilityState& highAvailabilityState)
    {
        std::string buf;
        is >> buf;
        highAvailabilityState = HighAvailabilityStateManager::toEnum(buf);
        return is;
    };

}
/* namespace SAFplusAmf */