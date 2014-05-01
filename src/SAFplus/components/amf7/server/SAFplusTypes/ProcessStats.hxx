/* 
 * File ProcessStats.hxx
 * This file has been auto-generated by Y2CPP, the
 * plug-in of pyang.
 */ 

#pragma once
#ifndef PROCESSSTATS_HXX_
#define PROCESSSTATS_HXX_
#include "SAFplusTypesCommon.hxx"

#include "clMgtObject.hxx"
#include "MemUtilization.hxx"
#include "CpuUtilization.hxx"
#include "MemUtilization.hxx"
#include "Failures.hxx"
#include <vector>
#include "MgtFactory.hxx"
#include "Failures.hxx"
#include "CpuUtilization.hxx"

namespace SAFplusTypes
  {

    class ProcessStats : public ClMgtObject {

        /* Apply MGT object factory */
        REGISTER(ProcessStats);

    public:

    public:
        ProcessStats();
        std::vector<std::string>* getChildNames();

        /*
         * XPATH: /SAFplusTypes/processStats/failures
         */
        SAFplusTypes::Failures* getFailures();

        /*
         * XPATH: /SAFplusTypes/processStats/failures
         */
        void addFailures(SAFplusTypes::Failures *failuresValue);

        /*
         * XPATH: /SAFplusTypes/processStats/cpuUtilization
         */
        SAFplusTypes::CpuUtilization* getCpuUtilization();

        /*
         * XPATH: /SAFplusTypes/processStats/cpuUtilization
         */
        void addCpuUtilization(SAFplusTypes::CpuUtilization *cpuUtilizationValue);

        /*
         * XPATH: /SAFplusTypes/processStats/memUtilization
         */
        SAFplusTypes::MemUtilization* getMemUtilization();

        /*
         * XPATH: /SAFplusTypes/processStats/memUtilization
         */
        void addMemUtilization(SAFplusTypes::MemUtilization *memUtilizationValue);
        ~ProcessStats();

    };
}
/* namespace SAFplusTypes */
#endif /* PROCESSSTATS_HXX_ */
