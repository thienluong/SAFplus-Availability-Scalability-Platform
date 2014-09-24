/* 
 * File StreamConfig.cxx
 * This file has been auto-generated by Y2CPP, the
 * plug-in of pyang.
 */ 
#include "SAFplusLogCommon.hxx"

#include "clMgtList.hxx"
#include <vector>
#include "MgtFactory.hxx"
#include "clMgtContainer.hxx"
#include "StreamConfig.hxx"


namespace SAFplusLog
  {

    /* Apply MGT object factory */
    MGT_REGISTER_IMPL(StreamConfig, /SAFplusLog/StreamConfig)

    StreamConfig::StreamConfig(): SAFplus::MgtContainer("StreamConfig"), streamList("stream")
    {
        this->addChildObject(&streamList, "stream");
        streamList.setListKey("myName");
    };

    std::vector<std::string>* StreamConfig::getChildNames()
    {
        std::string childNames[] = { "stream" };
        return new std::vector<std::string> (childNames, childNames + sizeof(childNames) / sizeof(childNames[0]));
    };

    StreamConfig::~StreamConfig()
    {
    };

}
/* namespace SAFplusLog */
