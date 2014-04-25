/* 
 * File ReadinessState.hxx
 * This file has been auto-generated by Y2CPP, the
 * plug-in of pyang.
 */ 

#ifndef READINESSSTATE_HXX_
#define READINESSSTATE_HXX_

#include "MgtEnumType.hxx"
#include <iostream>

namespace SAFplusAmf {

    enum class ReadinessState {
        outOfService, inService, stopping
    };
    std::ostream& operator<<(std::ostream& os, const ReadinessState& e);
    std::istream& operator>>(std::istream& is, ReadinessState& e);

    /*
     * This is the class that will handle the conversion for us.
     */
    class ReadinessStateManager : public SAFplus::MgtEnumType<ReadinessStateManager, ReadinessState> {
        ReadinessStateManager();  // private to prevent instantiation
    public:
        static const vec_t en2str_vec;  // This is the lookup table.
    };
}
/* namespace SAFplusAmf */
#endif /* READINESSSTATE_HXX_ */
