/* 
 * File StandbyWeight.hxx
 * This file has been auto-generated by Y2CPP, the
 * plug-in of pyang.
 */ 

#pragma once
#ifndef STANDBYWEIGHT_HXX_
#define STANDBYWEIGHT_HXX_

#include "MgtFactory.hxx"
#include "Capacity.hxx"
#include <string>
#include "SAFplusAmfCommon.hxx"
#include <vector>

namespace SAFplusAmf
  {

    class StandbyWeight : public Capacity {

        /* Apply MGT object factory */
        MGT_REGISTER(StandbyWeight);

    public:
        StandbyWeight();
        StandbyWeight(std::string resourceValue);
        std::vector<std::string> getKeys();
        std::vector<std::string>* getChildNames();
        ~StandbyWeight();

    };
}
/* namespace ::SAFplusAmf */
#endif /* STANDBYWEIGHT_HXX_ */
