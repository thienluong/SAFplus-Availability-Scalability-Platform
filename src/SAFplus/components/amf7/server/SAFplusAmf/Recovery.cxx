/* 
 * File Recovery.cxx
 * This file has been auto-generated by Y2CPP, the
 * plug-in of pyang.
 */ 
#include "SAFplusAmfCommon.hxx"

#include "MgtEnumType.hxx"
#include <iostream>
#include "Recovery.hxx"


namespace SAFplusAmf
  {

    /*
     * Provide an implementation of the en2str_vec lookup table.
     */
    const RecoveryManager::vec_t RecoveryManager::en2str_vec = {
            pair_t(Recovery::NoRecommendation, "NoRecommendation"),
            pair_t(Recovery::Restart, "Restart"),
            pair_t(Recovery::Failover, "Failover"),
            pair_t(Recovery::NodeSwitchover, "NodeSwitchover"),
            pair_t(Recovery::NodeFailover, "NodeFailover"),
            pair_t(Recovery::NodeFailfast, "NodeFailfast"),
            pair_t(Recovery::ClusterReset, "ClusterReset"),
            pair_t(Recovery::ApplicationRestart, "ApplicationRestart"),
            pair_t(Recovery::ContainerRestart, "ContainerRestart")
    }; // uses c++11 initializer lists 

    std::ostream& operator<<(std::ostream &os, const SAFplusAmf::Recovery &recovery)
    {
        return os << RecoveryManager::toString(recovery);
    };

    std::istream& operator>>(std::istream &is, SAFplusAmf::Recovery &recovery)
    {
        std::string buf;
        is >> buf;
        recovery = RecoveryManager::toEnum(buf);
        return is;
    };

}
/* namespace SAFplusAmf */
