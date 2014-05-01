/* 
 * File SpareServiceUnits.cxx
 * This file has been auto-generated by Y2CPP, the
 * plug-in of pyang.
 */ 

#include <vector>
#include "MgtFactory.hxx"
#include "clMgtObject.hxx"
#include "SpareServiceUnits.hxx"


namespace SAFplusAmf {

    /* Apply MGT object factory */
    REGISTERIMPL(SpareServiceUnits, /SAFplusAmf/ServiceGroup/spareServiceUnits)

    SpareServiceUnits::SpareServiceUnits(): ClMgtObject("spareServiceUnits")
    {
    };

    std::vector<std::string>* SpareServiceUnits::getChildNames()
    {
        std::string childNames[] = { "current", "history10sec", "history1min", "history10min", "history1hour", "history12hour", "history1day", "history1week", "history1month" };
        return new std::vector<std::string> (childNames, childNames + sizeof(childNames) / sizeof(childNames[0]));
    };

    SpareServiceUnits::~SpareServiceUnits()
    {
    };

}
/* namespace SAFplusAmf */
