/*
**  Copyright (C) 2012 Aldebaran Robotics
**  See COPYING for the license
*/
#include <iostream>
#include <vector>
#include <map>

#include <qimessaging/serviceinfo.hpp>
#include <qimessaging/datastream.hpp>

namespace qi
{

  ServiceInfo::ServiceInfo()
    : _name(),
      _serviceId(),
      _machineId(),
      _processId(),
      _endpoints(),
      _reserved(0)
  {
  }

  qi::ODataStream &operator<<(qi::ODataStream &stream, const ServiceInfo &sinfo) {
    stream << sinfo.name()
           << sinfo.serviceId()
           << sinfo.machineId()
           << sinfo.processId()
           << sinfo.endpoints();
    return stream;
  }

  qi::IDataStream &operator>>(qi::IDataStream &stream, ServiceInfo &sinfo) {
    stream >> sinfo._name;
    stream >> sinfo._serviceId;
    stream >> sinfo._machineId;
    stream >> sinfo._processId;
    stream >> sinfo._endpoints;
    return stream;
  }

  qi::SignatureStream &operator&(qi::SignatureStream &stream, const ServiceInfo &sinfo) {
    stream.write(qi::Signature::Type_Tuple);
    stream & sinfo.name();
    stream & sinfo.serviceId();
    stream & sinfo.machineId();
    stream & sinfo.processId();
    stream & sinfo.endpoints();
    stream.write(qi::Signature::Type_Tuple_End);
    return stream;
  }

}; // !qi