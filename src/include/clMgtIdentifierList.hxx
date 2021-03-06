/*
 * Copyright (C) 2002-2013 OpenClovis Solutions Inc.  All Rights Reserved.
 *
 * This file is available  under  a  commercial  license  from  the
 * copyright  holder or the GNU General Public License Version 2.0.
 *
 * The source code for  this program is not published  or otherwise
 * divested of  its trade secrets, irrespective  of  what  has been
 * deposited with the U.S. Copyright office.
 *
 * This program is distributed in the  hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied  warranty  of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * For more  information, see  the file  COPYING provided with this
 * material.
 */

/**
 *  \file
 *  \brief Header file of the MgtIdentifierList class which provides APIs to manage "instance identifier" objects
 *  \ingroup mgt
 */

/**
 *  \addtogroup mgt
 *  \{
 */

#ifndef CLMGTIDENTIFIERLIST_HXX_
#define CLMGTIDENTIFIERLIST_HXX_

#include "clMgtObject.hxx"
#include "clMgtRoot.hxx"

#include <typeinfo>
#include <iostream>
#include <iterator>
#include <fstream>
#include <sstream>
#include <vector>

namespace SAFplus
{
/*
 * Represents YANG leaf-list primitive
 */

template<class T>
class MgtIdentifierList: public MgtObject
{
public:
    typedef std::vector<T> ContainerType;
    std::vector<T> value;
    std::vector<std::string> refs;

public:
    MgtIdentifierList(const char* name);

    virtual ~MgtIdentifierList();

  virtual void toString(std::stringstream& xmlString, int depth=SAFplusI::MgtToStringRecursionDepth, SerializationOptions opts=SerializeNoOptions);

    /**
     * \brief   Virtual function to validate object data
     */
    virtual ClBoolT set(const void *pBuffer, ClUint64T buffLen, SAFplus::Transaction& t);

    /**
     * \brief   Virtual function to validate object data; throws transaction exception if fails
     */
    std::string toStringItemAt(T x);

    void pushBackValue(T strVal);

    void push_back(T val) { value.push_back(val); }

    typename ContainerType::iterator find(T item)
    {
      typename ContainerType::iterator it;
      for (it=value.begin(); it!=value.end(); it++)
      {
        if (item == *it) return it;
      }
      return it;
    }

    bool contains(T item)
    {
      if (find(item) == value.end()) return false;
      return true;
    }

    //? Remove all elements
    void clear() 
    { 
      // TODO: should we also clear refs?
      value.clear(); 
    }

    /*? Remove the first element that == item */
    void erase(T item)
    {
      typename std::vector<T>::iterator it;
      for (it=value.begin(); it!=value.end(); it++)
      {
        // TODO: should we also remove the equivalent index in refs?
        if (item == *it) 
          {
          value.erase(it);
          return;
          }
      }
    }

    virtual ClRcT write(MgtDatabase* db, std::string xpt = "")
    {
      return CL_OK;
    }
    virtual ClRcT read(MgtDatabase *db, std::string xpt = "")
    {
      std::string key;
      if(xpt.size() > 0)
      {
        key.assign(xpt);
        key.append(getFullXpath(false));
      }
      else
        key.assign(getFullXpath(true));
      if(db == nullptr)
      {
        db = MgtDatabase::getInstance();
      }
      if(!db->isInitialized())
      {
        return CL_ERR_NOT_INITIALIZED;
      }

      std::vector<std::string> iter;
      db->iterate(key, iter);

      refs.clear();
      for (std::vector<std::string>::iterator it=iter.begin(); it!=iter.end(); it++)
      {
        std::string value;
        if (db->getRecord(*it, value) == CL_OK)
        {
          refs.push_back(value);
        }
      }
      MgtRoot *mgtRoot = MgtRoot::getInstance();
      mgtRoot->addReference(this);
      dataXPath.assign(key);
      loadDb = true;

      return CL_OK;
    }

    void updateReference()
    {
      MgtObject *objRoot = dynamic_cast<MgtObject *>(this->root());
      value.clear();
      for ( std::vector<std::string>::iterator it = refs.begin();
          it != refs.end();
          it++)
        {
          std::string ref = *it;
          MgtObject *obj = objRoot->lookUpMgtObject(typeid(T).name(), ref);
          if (obj)
          {
            value.push_back((T)obj);
          }
        }
    }
};

template<class T>
MgtIdentifierList<T>::MgtIdentifierList(const char* name) :
  MgtObject(name)
{
}

template<class T>
MgtIdentifierList<T>::~MgtIdentifierList()
{
}

template<class T>
std::string MgtIdentifierList<T>::toStringItemAt(T x)
{
    std::stringstream ss;

    MgtObject *obj = dynamic_cast<MgtObject *>(x);
    if (obj)
        ss << x->getFullXpath();

    return ss.str();
}

template<class T>
void MgtIdentifierList<T>::toString(std::stringstream& xmlString, int depth, SerializationOptions opts)
{
  xmlString << '<' << tag;
  if (opts & MgtObject::SerializeNameAttribute)
    xmlString << " name=" << "\"" << getFullXpath(false) << "\"";
  if (opts & MgtObject::SerializePathAttribute)
    xmlString << " path=" << "\"" << getFullXpath(true) << "\"";
  xmlString << '>';                

  int len = value.size();
  for (unsigned int i = 0; i < len; i++)
    {
      xmlString << toStringItemAt(value.at(i));
      if (i+1<len) xmlString << ", ";
    }

  xmlString << "</" << tag << ">";
}

template<class T>
ClBoolT MgtIdentifierList<T>::set(const void *pBuffer, ClUint64T buffLen, SAFplus::Transaction& t)
{
    return CL_FALSE;
}

template<class T>
void MgtIdentifierList<T>::pushBackValue(T val)
{
    value.push_back(val);
}

};
#endif /* CLMGTIDENTIFIERLIST_HXX_ */
