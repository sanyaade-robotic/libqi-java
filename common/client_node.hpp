#pragma once
/*
** Author(s):
**  - Chris Kilner <ckilner@aldebaran-robotics.com>
**
** Copyright (C) 2010 Aldebaran Robotics
*/
#ifndef COMMON_CLIENT_NODE_HPP_
#define COMMON_CLIENT_NODE_HPP_

#include <string>
#include <alcommon-ng/messaging/messaging.hpp>
#include <alcommon-ng/common/mutexednamelookup.hpp>
#include <alcommon-ng/common/namelookup.hpp>
#include <alcommon-ng/common/nodeinfo.hpp>
#include <alcommon-ng/common/serviceinfo.hpp>

namespace AL {
  namespace Common {

    // can handle calls to any service known by master
    class ClientNode {
    public:
      ClientNode(const std::string& clientName,
        const std::string& masterAddress);
      virtual ~ClientNode();

      // TODO use templated real calls ...
      AL::Messaging::ResultDefinition call(
        const AL::Messaging::CallDefinition& callDef);


    private:
      // TODO Hide implementation
      std::string fClientName;
      std::string fMasterAddress;

      // not really needed, except when we need the node address to make a client
      NameLookup<NodeInfo> fServerList;

      // should be map from hash to nodeName
      MutexedNameLookup<ServiceInfo> fServiceCache;

      // map from nodeName to Client
      NameLookup<boost::shared_ptr<AL::Messaging::DefaultClient> > fServerClients;

      void xInit();
      void xUpdateServicesFromMaster();
      void xCreateServerClient(const NodeInfo& serverNodeInfo);

      const std::string xLocateService(const std::string& methodHash);

      

    };
  }
}

#endif  // COMMON_CLIENT_NODE_HPP_

