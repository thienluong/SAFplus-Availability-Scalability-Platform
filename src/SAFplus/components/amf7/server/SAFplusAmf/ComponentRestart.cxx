/* 
 * File ComponentRestart.cxx
 * This file has been auto-generated by Y2CPP, the
 * plug-in of pyang.
 */ 
#include "SAFplusAmfCommon.hxx"

#include <vector>
#include "MgtFactory.hxx"
#include "clMgtObject.hxx"
#include "ComponentRestart.hxx"


namespace SAFplusAmf
  {

    /* Apply MGT object factory */
    REGISTERIMPL(ComponentRestart, /SAFplusAmf/ServiceGroup/componentRestart)

    ComponentRestart::ComponentRestart(): ClMgtObject("componentRestart")
    {
    };

    std::vector<std::string>* ComponentRestart::getChildNames()
    {
        std::string childNames[] = { "maximum", "duration" };
        return new std::vector<std::string> (childNames, childNames + sizeof(childNames) / sizeof(childNames[0]));
    };

    ComponentRestart::~ComponentRestart()
    {
    };

}
/* namespace SAFplusAmf */
