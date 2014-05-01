/* 
 * File MemUtilization.hxx
 * This file has been auto-generated by Y2CPP, the
 * plug-in of pyang.
 */ 

#pragma once
#ifndef MEMUTILIZATION_HXX_
#define MEMUTILIZATION_HXX_
#include "SAFplusTypesCommon.hxx"

#include <vector>
#include "MgtFactory.hxx"
#include "clMgtObject.hxx"

namespace SAFplusTypes
  {

    class MemUtilization : public ClMgtObject {

        /* Apply MGT object factory */
        REGISTER(MemUtilization);

    public:

    public:
        MemUtilization();
        std::vector<std::string>* getChildNames();
        ~MemUtilization();

    };
}
/* namespace SAFplusTypes */
#endif /* MEMUTILIZATION_HXX_ */
