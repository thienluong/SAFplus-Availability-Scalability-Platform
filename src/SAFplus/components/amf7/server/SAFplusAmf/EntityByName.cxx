/* 
 * File EntityByName.cxx
 * This file has been auto-generated by Y2CPP, the
 * plug-in of pyang.
 */ 
#include "SAFplusAmfCommon.hxx"

#include "clMgtObject.hxx"
#include "clMgtProv.hxx"
#include <vector>
#include "MgtFactory.hxx"
#include <string>
#include "EntityByName.hxx"


namespace SAFplusAmf
  {

    /* Apply MGT object factory */
    REGISTERIMPL(EntityByName, /SAFplusAmf/EntityByName)

    EntityByName::EntityByName(): ClMgtObject("EntityByName"), name("name"), entity("entity")
    {
        this->addChildObject(&name, "name");
        this->addChildObject(&entity, "entity");
    };

    std::vector<std::string>* EntityByName::getChildNames()
    {
        std::string childNames[] = { "name", "entity" };
        return new std::vector<std::string> (childNames, childNames + sizeof(childNames) / sizeof(childNames[0]));
    };

    /*
     * XPATH: /SAFplusAmf/EntityByName/name
     */
    std::string EntityByName::getName()
    {
        return this->name.Value;
    };

    /*
     * XPATH: /SAFplusAmf/EntityByName/name
     */
    void EntityByName::setName(std::string nameValue)
    {
        this->name.Value = nameValue;
    };

    /*
     * XPATH: /SAFplusAmf/EntityByName/entity
     */
    std::string EntityByName::getEntity()
    {
        return this->entity.Value;
    };

    /*
     * XPATH: /SAFplusAmf/EntityByName/entity
     */
    void EntityByName::setEntity(std::string entityValue)
    {
        this->entity.Value = entityValue;
    };

    EntityByName::~EntityByName()
    {
    };

}
/* namespace SAFplusAmf */
