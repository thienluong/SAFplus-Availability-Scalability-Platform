/* 
 * File RestartCount.hxx
 * This file has been auto-generated by Y2CPP, the
 * plug-in of pyang.
 */ 

#pragma once
#ifndef RESTARTCOUNT_HXX_
#define RESTARTCOUNT_HXX_
#include "SAFplusAmfCommon.hxx"

#include <vector>
#include "MgtFactory.hxx"
#include "IntStatistic.hxx"

namespace SAFplusAmf
  {

    class RestartCount : public SAFplusTypes::IntStatistic {

        /* Apply MGT object factory */
        MGT_REGISTER(RestartCount);

    public:

    public:
        RestartCount();
        std::vector<std::string>* getChildNames();
        ~RestartCount();

    };
}
/* namespace SAFplusAmf */
#endif /* RESTARTCOUNT_HXX_ */
