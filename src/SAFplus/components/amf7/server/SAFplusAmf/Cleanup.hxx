/* 
 * File Cleanup.hxx
 * This file has been auto-generated by Y2CPP, the
 * plug-in of pyang.
 */ 

#pragma once
#ifndef CLEANUP_HXX_
#define CLEANUP_HXX_
#include "SAFplusAmfCommon.hxx"

#include "Execution.hxx"
#include <vector>
#include "MgtFactory.hxx"

namespace SAFplusAmf
  {

    class Cleanup : public Execution {

        /* Apply MGT object factory */
        MGT_REGISTER(Cleanup);

    public:

    public:
        Cleanup();
        std::vector<std::string>* getChildNames();
        ~Cleanup();

    };
}
/* namespace SAFplusAmf */
#endif /* CLEANUP_HXX_ */
