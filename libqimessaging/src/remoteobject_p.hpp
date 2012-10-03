#pragma once
/*
**  Copyright (C) 2012 Aldebaran Robotics
**  See COPYING for the license
*/

#ifndef _SRC_REMOTEOBJECT_P_HPP_
#define _SRC_REMOTEOBJECT_P_HPP_

#include <qimessaging/datastream.hpp>
#include <qimessaging/transportsocket.hpp>
#include <qimessaging/genericobject.hpp>
#include <qimessaging/dynamicobject.hpp>
#include <qimessaging/signal.hpp>

#include "src/messagedispatcher.hpp"
#include "src/object_p.hpp"

#include <boost/thread/mutex.hpp>
#include <string>

namespace qi {

  class TransportSocket;



  class RemoteObject : public qi::DynamicObject {
  public:
    RemoteObject();
    RemoteObject(unsigned int service, qi::MetaObject metaObject, qi::TransportSocketPtr socket = qi::TransportSocketPtr());
    ~RemoteObject();

    void setTransportSocket(qi::TransportSocketPtr socket);
    void close();

  protected:
    //MessageDispatcher callback
    void onMessagePending(const qi::Message &msg);

    virtual void metaEmit(unsigned int event, const GenericFunctionParameters& args);
    virtual qi::Future<GenericValue> metaCall(unsigned int method, const GenericFunctionParameters& args, qi::MetaCallType callType = qi::MetaCallType_Auto);
    virtual unsigned int connect(unsigned int event, const SignalSubscriber& sub);
    virtual bool disconnect(unsigned int linkId);
  public:
    TransportSocketPtr          _socket;

  protected:
    unsigned int                                    _service;
    std::map<int, qi::Promise<GenericValue> > _promises;
    boost::mutex    _mutex;
    qi::SignalBase::Link                            _linkMessageDispatcher;
  };

}



#endif  // _SRC_REMOTEOBJECT_P_HPP_
