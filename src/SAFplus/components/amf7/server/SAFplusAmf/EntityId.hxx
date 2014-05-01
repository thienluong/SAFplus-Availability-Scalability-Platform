/* 
 * File EntityId.hxx
 * This file has been auto-generated by Y2CPP, the
 * plug-in of pyang.
 */ 

#pragma once
#ifndef ENTITYID_HXX_
#define ENTITYID_HXX_
#include "SAFplusAmfCommon.hxx"

#include "clMgtObject.hxx"
#include "clMgtProv.hxx"
#include <vector>
#include "MgtFactory.hxx"
#include <string>

namespace SAFplusAmf
  {

    class EntityId : public ClMgtObject {

        /* Apply MGT object factory */
        REGISTER(EntityId);

    public:

        /*
         * Unique name of this entity
         */
        ClMgtProv<std::string> name;

        /*
         * Each SAFplus AMF entity gets a unique numerical identifier
         */
        ClMgtProv<unsigned short int> id;

    public:
        EntityId();
        std::vector<std::string>* getChildNames();

        /*
         * XPATH: /SAFplusAmf/EntityId/name
         */
        std::string getName();

        /*
         * XPATH: /SAFplusAmf/EntityId/name
         */
        void setName(std::string nameValue);

        /*
         * XPATH: /SAFplusAmf/EntityId/id
         */
        unsigned short int getId();

        /*
         * XPATH: /SAFplusAmf/EntityId/id
         */
        void setId(unsigned short int idValue);
        ~EntityId();

    };
}
/* namespace SAFplusAmf */
#endif /* ENTITYID_HXX_ */
