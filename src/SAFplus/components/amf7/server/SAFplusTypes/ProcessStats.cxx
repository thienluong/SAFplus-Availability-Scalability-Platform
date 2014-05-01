/* 
 * File ProcessStats.cxx
 * This file has been auto-generated by Y2CPP, the
 * plug-in of pyang.
 */ 
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
#include "ProcessStats.hxx"


namespace SAFplusTypes
  {

    /* Apply MGT object factory */
    REGISTERIMPL(ProcessStats, /processStats)

    ProcessStats::ProcessStats(): ClMgtObject("processStats")
    {
    };

    std::vector<std::string>* ProcessStats::getChildNames()
    {
        std::string childNames[] = { "failures", "cpuUtilization", "memUtilization" };
        return new std::vector<std::string> (childNames, childNames + sizeof(childNames) / sizeof(childNames[0]));
    };

    /*
     * XPATH: /SAFplusTypes/processStats/failures
     */
    SAFplusTypes::Failures* ProcessStats::getFailures()
    {
        return (Failures*)this->getChildObject("failures");
    };

    /*
     * XPATH: /SAFplusTypes/processStats/failures
     */
    void ProcessStats::addFailures(SAFplusTypes::Failures *failuresValue)
    {
        this->addChildObject(failuresValue, "failures");
    };

    /*
     * XPATH: /SAFplusTypes/processStats/cpuUtilization
     */
    SAFplusTypes::CpuUtilization* ProcessStats::getCpuUtilization()
    {
        return (CpuUtilization*)this->getChildObject("cpuUtilization");
    };

    /*
     * XPATH: /SAFplusTypes/processStats/cpuUtilization
     */
    void ProcessStats::addCpuUtilization(SAFplusTypes::CpuUtilization *cpuUtilizationValue)
    {
        this->addChildObject(cpuUtilizationValue, "cpuUtilization");
    };

    /*
     * XPATH: /SAFplusTypes/processStats/memUtilization
     */
    SAFplusTypes::MemUtilization* ProcessStats::getMemUtilization()
    {
        return (MemUtilization*)this->getChildObject("memUtilization");
    };

    /*
     * XPATH: /SAFplusTypes/processStats/memUtilization
     */
    void ProcessStats::addMemUtilization(SAFplusTypes::MemUtilization *memUtilizationValue)
    {
        this->addChildObject(memUtilizationValue, "memUtilization");
    };

    ProcessStats::~ProcessStats()
    {
    };

}
/* namespace SAFplusTypes */
