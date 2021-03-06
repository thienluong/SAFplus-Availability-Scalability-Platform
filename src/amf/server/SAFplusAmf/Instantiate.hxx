/* 
 * File Instantiate.hxx
 * This file has been auto-generated by Y2CPP, the
 * plug-in of pyang.
 */ 

#pragma once
#ifndef INSTANTIATE_HXX_
#define INSTANTIATE_HXX_

#include "SAFplusAmfCommon.hxx"
#include <vector>
#include "Execution.hxx"
#include "MgtFactory.hxx"

namespace SAFplusAmf
  {

    class Instantiate : public Execution {

        /* Apply MGT object factory */
        MGT_REGISTER(Instantiate);

    public:
        Instantiate();
        std::vector<std::string>* getChildNames();
        ~Instantiate();

    };
}
/* namespace ::SAFplusAmf */
#endif /* INSTANTIATE_HXX_ */
