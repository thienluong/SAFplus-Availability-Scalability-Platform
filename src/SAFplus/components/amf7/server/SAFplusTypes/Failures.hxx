/* 
 * File Failures.hxx
 * This file has been auto-generated by Y2CPP, the
 * plug-in of pyang.
 */ 

#pragma once
#ifndef FAILURES_HXX_
#define FAILURES_HXX_
#include "SAFplusTypesCommon.hxx"

#include <vector>
#include "MgtFactory.hxx"
#include "clMgtObject.hxx"

namespace SAFplusTypes
  {

    class Failures : public ClMgtObject {

        /* Apply MGT object factory */
        REGISTER(Failures);

    public:

    public:
        Failures();
        std::vector<std::string>* getChildNames();
        ~Failures();

    };
}
/* namespace SAFplusTypes */
#endif /* FAILURES_HXX_ */
