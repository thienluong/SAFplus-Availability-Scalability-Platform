/* 
 * File AssignedServiceUnits.cxx
 * This file has been auto-generated by Y2CPP, the
 * plug-in of pyang.
 */ 

#include <vector>
#include "MgtFactory.hxx"
#include "clMgtObject.hxx"
#include "AssignedServiceUnits.hxx"


namespace SAFplusAmf {

    /* Apply MGT object factory */
    REGISTERIMPL(AssignedServiceUnits, /SAFplusAmf/ServiceGroup/assignedServiceUnits)

    AssignedServiceUnits::AssignedServiceUnits(): ClMgtObject("assignedServiceUnits")
    {
    };

    std::vector<std::string>* AssignedServiceUnits::getChildNames()
    {
        std::string childNames[] = { "current", "history10sec", "history1min", "history10min", "history1hour", "history12hour", "history1day", "history1week", "history1month" };
        return new std::vector<std::string> (childNames, childNames + sizeof(childNames) / sizeof(childNames[0]));
    };

    AssignedServiceUnits::~AssignedServiceUnits()
    {
    };

}
/* namespace SAFplusAmf */
