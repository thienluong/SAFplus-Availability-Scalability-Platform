/* 
 * File PhysAddress.hxx
 * This file has been auto-generated by Y2CPP, the
 * plug-in of pyang.
 */ 

#ifndef PHYSADDRESS_HXX_
#define PHYSADDRESS_HXX_

#include <iostream>
#include <string>

namespace ietfYangTypes {

    class PhysAddress {
    public:
        std::string Value;

    public:
        PhysAddress();
        std::string getValue();
        void setValue(std::string value);
        ietfYangTypes::PhysAddress& operator=(const ietfYangTypes::PhysAddress& physAddress);
        friend std::ostream& operator<<(std::ostream& os, const ietfYangTypes::PhysAddress& physAddress);
        friend std::istream& operator>>(std::istream& is, ietfYangTypes::PhysAddress& physAddress);
        ~PhysAddress();

    };
}
/* namespace ietfYangTypes */
#endif /* PHYSADDRESS_HXX_ */
