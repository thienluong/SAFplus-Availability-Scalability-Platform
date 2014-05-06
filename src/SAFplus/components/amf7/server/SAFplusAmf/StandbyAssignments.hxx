/* 
 * File StandbyAssignments.hxx
 * This file has been auto-generated by Y2CPP, the
 * plug-in of pyang.
 */ 

#pragma once
#ifndef STANDBYASSIGNMENTS_HXX_
#define STANDBYASSIGNMENTS_HXX_
#include "SAFplusAmfCommon.hxx"

#include <vector>
#include "MgtFactory.hxx"
#include "IntStatistic.hxx"

namespace SAFplusAmf
  {

    class StandbyAssignments : public SAFplusTypes::IntStatistic {

        /* Apply MGT object factory */
        MGT_REGISTER(StandbyAssignments);

    public:

    public:
        StandbyAssignments();
        std::vector<std::string>* getChildNames();
        ~StandbyAssignments();

    };
}
/* namespace SAFplusAmf */
#endif /* STANDBYASSIGNMENTS_HXX_ */
