/*
*  Author(s):
*  - Cedric Gestes <gestes@aldebaran-robotics.com>
*  - Herve Cuche <hcuche@aldebaran-robotics.com>
*
*  Copyright (C) 2012 Aldebaran Robotics
*/

#include <qimessaging/broker.hpp>
#include <qimessaging/transport.hpp>

namespace qi {

Broker::Broker()
{
  tc = new qi::TransportSocket();
  tc->setDelegate(this);
}

Broker::~Broker()
{
  tc->disconnect();
  delete tc;
}

void Broker::connect(const std::string masterAddress)
{
  tc->connect("127.0.0.1", 5555, nthd->getEventBase());
}

void Broker::setThread(qi::NetworkThread *n)
{
  nthd = n;
}

bool Broker::disconnect()
{
}


bool Broker::waitForConnected(int msecs)
{
  return tc->waitForConnected(msecs);
}

bool Broker::waitForDisconnected(int msecs)
{
  return tc->waitForDisconnected(msecs);
}


void Broker::registerMachine(const qi::MachineInfo& m)
{
}

void Broker::unregisterMachine(const qi::MachineInfo& m)
{
}


bool Broker::isInitialized() const
{
}

std::vector<std::string> Broker::machines()
{
  std::vector<std::string> result;

  qi::Message msg;

  msg.setId(0);
  msg.setSource("moi");
  msg.setDestination("qi.servicedirectorymanager");
  msg.setPath("machines");

  tc->send(msg);
  tc->waitForId(msg.id());
  qi::Message ans;
  tc->read(msg.id(), &ans);

  std::cout << ans << std::endl;

  return result;
}

void Broker::onConnected(const qi::Message &msg)
{
  std::cout << "connected: " << std::endl;
}

void Broker::onWrite(const qi::Message &msg)
{
  std::cout << "written: " << std::endl;
}

void Broker::onRead(const qi::Message &msg)
{
  std::cout << "read: " << std::endl;
}


}