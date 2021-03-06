/* 
 * File ProcessState.cxx
 * This file has been auto-generated by Y2CPP, the
 * plug-in of pyang.
 */ 

#include "MgtEnumType.hxx"
#include "SAFplusTypesCommon.hxx"
#include <iostream>
#include "ProcessState.hxx"

using namespace SAFplusTypes;

namespace SAFplusTypes
  {

    /*
     * Provide an implementation of the en2str_map lookup table.
     */
    const ProcessStateManager::map_t ProcessStateManager::en2str_map = {
            pair_t(ProcessState::Running, "Running"),
            pair_t(ProcessState::Sleeping, "Sleeping"),
            pair_t(ProcessState::WaitingForDisk, "WaitingForDisk"),
            pair_t(ProcessState::Zombie, "Zombie"),
            pair_t(ProcessState::Stopped, "Stopped"),
            pair_t(ProcessState::TracingStop, "TracingStop")
    }; // uses c++11 initializer lists 

    const char* c_str(const SAFplusTypes::ProcessState &processState)
    {
        return ProcessStateManager::c_str(processState);
    };

    std::ostream& operator<<(std::ostream &os, const SAFplusTypes::ProcessState &processState)
    {
        return os << ProcessStateManager::toString(processState);
    };

    std::istream& operator>>(std::istream &is, SAFplusTypes::ProcessState &processState)
    {
        std::string buf;
        is >> buf;
        processState = ProcessStateManager::toEnum(buf);
        return is;
    };

}
/* namespace ::SAFplusTypes */
