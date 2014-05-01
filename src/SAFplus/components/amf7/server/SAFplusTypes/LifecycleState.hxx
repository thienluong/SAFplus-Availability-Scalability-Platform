/* 
 * File LifecycleState.hxx
 * This file has been auto-generated by Y2CPP, the
 * plug-in of pyang.
 */ 

#pragma once
#ifndef LIFECYCLESTATE_HXX_
#define LIFECYCLESTATE_HXX_
#include "SAFplusTypesCommon.hxx"

#include "MgtEnumType.hxx"
#include <iostream>

namespace SAFplusTypes
  {

    enum class LifecycleState
  {
        start, idle, stop
      };
    std::ostream& operator<<(std::ostream& os, const LifecycleState& e);
    std::istream& operator>>(std::istream& is, LifecycleState& e);

    /*
     * This is the class that will handle the conversion for us.
     */
    class LifecycleStateManager : public SAFplus::MgtEnumType<LifecycleStateManager, LifecycleState> {
        LifecycleStateManager();  // private to prevent instantiation
    public:
        static const vec_t en2str_vec;  // This is the lookup table.
    };
}
/* namespace SAFplusTypes */
#endif /* LIFECYCLESTATE_HXX_ */
