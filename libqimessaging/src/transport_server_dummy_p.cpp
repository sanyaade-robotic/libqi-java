/*
 ** transport-server.cpp
 ** Login : <hcuche@hcuche-de>
 ** Started on  Wed Jan 11 10:19:42 2012 Herve Cuche
 ** $Id$
 **
 ** Author(s):
 **  - Herve Cuche <hcuche@aldebaran-robotics.com>
 **
 ** Copyright (C) 2012 Herve Cuche
 */

#include <iostream>
#include <qi/log.hpp>

#include <qimessaging/session.hpp>
#include <qimessaging/url.hpp>
#include "src/transport_server_p.hpp"
#include "src/transport_server_dummy_p.hpp"

namespace qi
{
  bool TransportServerDummyPrivate::start()
  {
    qiLogWarning("TransportServer") << "You are currently running on dummy"
                                    << " TransportServer!";
    return true;
  }

  TransportServerDummyPrivate::TransportServerDummyPrivate(qi::Session *session,
                                                           const qi::Url &url)
    : TransportServerPrivate(session, url)
  {
  }

  TransportServerDummyPrivate::~TransportServerDummyPrivate()
  {
  }
}