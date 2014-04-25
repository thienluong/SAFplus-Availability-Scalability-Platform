/* 
 * File ServiceUnitRestart.hxx
 * This file has been auto-generated by Y2CPP, the
 * plug-in of pyang.
 */ 

#ifndef SERVICEUNITRESTART_HXX_
#define SERVICEUNITRESTART_HXX_

#include "clMgtObject.hxx"
#include "clMgtProv.hxx"
#include "SaTimeT.hxx"
#include <vector>
#include "MgtFactory.hxx"

namespace SAFplusAmf {

    class ServiceUnitRestart : public ClMgtObject {

        /* Apply MGT object factory */
        REGISTER(ServiceUnitRestart);

    public:

        /*
         * The maximum number of events that can occur within that time period before escalation occurs.
         */
        ClMgtProv<unsigned long int> maximum;

        /*
         * The time period (in milliseconds) involved.
         */
        ClMgtProv<SAFplusTypes::SaTimeT> duration;

    public:
        ServiceUnitRestart();
        std::vector<std::string>* getChildNames();

        /*
         * XPATH: /SAFplusAmf/ServiceGroup/ServiceUnitRestart/maximum
         */
        unsigned long int getMaximum();

        /*
         * XPATH: /SAFplusAmf/ServiceGroup/ServiceUnitRestart/maximum
         */
        void setMaximum(unsigned long int maximumValue);

        /*
         * XPATH: /SAFplusAmf/ServiceGroup/ServiceUnitRestart/duration
         */
        SAFplusTypes::SaTimeT getDuration();

        /*
         * XPATH: /SAFplusAmf/ServiceGroup/ServiceUnitRestart/duration
         */
        void setDuration(SAFplusTypes::SaTimeT durationValue);
        ~ServiceUnitRestart();

    };
}
/* namespace SAFplusAmf */
#endif /* SERVICEUNITRESTART_HXX_ */
