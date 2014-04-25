/* 
 * File HighAvailabilityState.hxx
 * This file has been auto-generated by Y2CPP, the
 * plug-in of pyang.
 */ 

#ifndef HIGHAVAILABILITYSTATE_HXX_
#define HIGHAVAILABILITYSTATE_HXX_

#include "MgtEnumType.hxx"
#include <iostream>

namespace SAFplusAmf {

    enum class HighAvailabilityState {
        active, standby, quiescing, idle
    };
    std::ostream& operator<<(std::ostream& os, const HighAvailabilityState& e);
    std::istream& operator>>(std::istream& is, HighAvailabilityState& e);

    /*
     * This is the class that will handle the conversion for us.
     */
    class HighAvailabilityStateManager : public SAFplus::MgtEnumType<HighAvailabilityStateManager, HighAvailabilityState> {
        HighAvailabilityStateManager();  // private to prevent instantiation
    public:
        static const vec_t en2str_vec;  // This is the lookup table.
    };
}
/* namespace SAFplusAmf */
#endif /* HIGHAVAILABILITYSTATE_HXX_ */
