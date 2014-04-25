/* 
 * File ObjectIdentifier.hxx
 * This file has been auto-generated by Y2CPP, the
 * plug-in of pyang.
 */ 

#ifndef OBJECTIDENTIFIER_HXX_
#define OBJECTIDENTIFIER_HXX_

#include <string>
#include <iostream>

namespace ietfYangTypes {

    class ObjectIdentifier {
    public:
        std::string Value;

    public:
        ObjectIdentifier();
        std::string getValue();
        void setValue(std::string value);
        ietfYangTypes::ObjectIdentifier& operator=(const ietfYangTypes::ObjectIdentifier& objectIdentifier);
        friend std::ostream& operator<<(std::ostream& os, const ietfYangTypes::ObjectIdentifier& objectIdentifier);
        friend std::istream& operator>>(std::istream& is, ietfYangTypes::ObjectIdentifier& objectIdentifier);
        ~ObjectIdentifier();

    };
}
/* namespace ietfYangTypes */
#endif /* OBJECTIDENTIFIER_HXX_ */