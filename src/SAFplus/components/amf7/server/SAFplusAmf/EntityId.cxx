/* 
 * File EntityId.cxx
 * This file has been auto-generated by Y2CPP, the
 * plug-in of pyang.
 */ 
#include "SAFplusAmfCommon.hxx"

#include <vector>
#include "clMgtObject.hxx"
#include "clMgtProv.hxx"
#include <string>
#include "EntityId.hxx"


namespace SAFplusAmf
  {

    EntityId::EntityId(): SAFplus::ClMgtObject("EntityId"), name("name"), id("id")
    {
        this->addChildObject(&name, "name");
        this->addChildObject(&id, "id");
    };

    std::vector<std::string>* EntityId::getChildNames()
    {
        std::string childNames[] = { "name", "id" };
        return new std::vector<std::string> (childNames, childNames + sizeof(childNames) / sizeof(childNames[0]));
    };

    /*
     * XPATH: /SAFplusAmf/EntityId/name
     */
    std::string EntityId::getName()
    {
        return this->name.Value;
    };

    /*
     * XPATH: /SAFplusAmf/EntityId/name
     */
    void EntityId::setName(std::string nameValue)
    {
        this->name.Value = nameValue;
    };

    /*
     * XPATH: /SAFplusAmf/EntityId/id
     */
    unsigned short int EntityId::getId()
    {
        return this->id.Value;
    };

    /*
     * XPATH: /SAFplusAmf/EntityId/id
     */
    void EntityId::setId(unsigned short int idValue)
    {
        this->id.Value = idValue;
    };

    EntityId::~EntityId()
    {
    };

}
/* namespace SAFplusAmf */
