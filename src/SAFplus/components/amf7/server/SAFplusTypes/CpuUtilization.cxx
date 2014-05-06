/* 
 * File CpuUtilization.cxx
 * This file has been auto-generated by Y2CPP, the
 * plug-in of pyang.
 */ 
#include "SAFplusTypesCommon.hxx"

#include "DecStatistic.hxx"
#include <vector>
#include "MgtFactory.hxx"
#include "CpuUtilization.hxx"


namespace SAFplusTypes
  {

    /* Apply MGT object factory */
    MGT_REGISTER_IMPL(CpuUtilization, /SAFplusTypes/processStats/cpuUtilization)

    CpuUtilization::CpuUtilization()
    {
    };

    std::vector<std::string>* CpuUtilization::getChildNames()
    {
        std::string childNames[] = { "current", "history10sec", "history1min", "history10min", "history1hour", "history12hour", "history1day", "history1week", "history1month" };
        return new std::vector<std::string> (childNames, childNames + sizeof(childNames) / sizeof(childNames[0]));
    };

    CpuUtilization::~CpuUtilization()
    {
    };

}
/* namespace SAFplusTypes */
