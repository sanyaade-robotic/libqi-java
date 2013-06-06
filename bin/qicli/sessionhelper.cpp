#include <boost/regex.hpp>

#include "sessionhelper.hpp"

SessionHelper::SessionHelper(std::string const& address, bool verbose)
  :_verbose(verbose)
{
  if (_verbose)
  {
    std::cout << "Connecting to [" << address << "] : ";
    std::cout.flush();
  }
  try
  {
    _session.connect(address);
  }
  catch (std::exception const& e)
  {
    if (_verbose)
    std::cout << e.what() << std::endl;
    throw e;
  }
  if (_verbose)
    std::cout << "OK" << std::endl;
}

SessionHelper::~SessionHelper()
{
  if (_verbose)
  {
    std::cout << "Closing session : ";
    std::cout.flush();
  }
  qi::FutureSync<void> fut = _session.close();
  if (fut.hasError() && _verbose)
    std::cout << "error while closing session: " << fut.error() << std::endl;
  if (_verbose)
    std::cout << "OK" << std::endl;
}

bool SessionHelper::getServiceSync(const std::string &serviceName, ServiceHelper &out)
{
  qi::FutureSync<qi::ObjectPtr> future = _session.service(serviceName);

  if (future.hasError())
  {
    std::cout << "\terror : " << future.error() << std::endl;
    return false;
  }

  out = future.value();
  return true;
}

void SessionHelper::_showServiceInfo(qi::ServiceInfo const& infos, bool verbose, bool number)
{
  if (!verbose)
  {
    if (number)
      std::cout << "[" << infos.serviceId() << "]";
    std::cout << infos.name() << std::endl;
    return ;
  }

  std::cout << "    service: " << infos.name() << std::endl
            << "         id: " << infos.serviceId() << std::endl
            << "    machine: " << infos.machineId() << std::endl
            << "    process: " << infos.processId() << std::endl
            << "  endpoints: " << std::endl;

  for (qi::UrlVector::const_iterator it_urls = infos.endpoints().begin(); it_urls != infos.endpoints().end(); ++it_urls)
    std::cout << "             " << it_urls->str() << std::endl;

  ServiceHelper service;

  if (!this->getServiceSync(infos.name(), service))
    return ;
  qi::details::printMetaObject(std::cout, service.objPtr()->metaObject());
}

void SessionHelper::showServiceInfo(std::string const& serviceName, bool verbose, bool number)
{
  std::vector<qi::ServiceInfo> servs = _session.services();

  unsigned int i;
  for (i = 0; i < servs.size(); ++i)
    if (servs[i].name() == serviceName)
      break;
  if (i == servs.size())
    return ;

  _showServiceInfo(servs[i], verbose, number);
}

void SessionHelper::showServiceInfo(unsigned int serviceId, bool verbose, bool number)
{
  std::vector<qi::ServiceInfo> servs = _session.services();

  unsigned int i;
  for (i = 0; i < servs.size(); ++i)
    if (servs[i].serviceId() == serviceId)
      break;
  if (i == servs.size())
    return ;

  _showServiceInfo(servs[i], verbose, number);
}

bool isNumber(std::string const& str)
{
  for (unsigned int i = 0; i < str.length(); ++i)
  {
    if (!::isdigit(str[i]))
      return false;
  }
  return true;
}

void SessionHelper::xShowServicesInfo(std::vector<std::string> const& patternVec, bool verbose, bool number)
{
  std::vector<qi::ServiceInfo> servs = _session.services();
  std::vector<std::string> matchServs;

  for (unsigned int u = 0; u < patternVec.size(); ++u)
  {
    if (isNumber(patternVec[u]))
      matchServs.push_back(patternVec[u]);
    else
    {
      boost::basic_regex<char> reg(patternVec[u]);
      for (unsigned int i = 0; i < servs.size(); ++i)
      {
        if (boost::regex_match(servs[i].name(), reg))
          matchServs.push_back(servs[i].name());
      }
    }
  }
  showServicesInfo(matchServs, verbose, number);
}

void SessionHelper::showServicesInfo(std::vector<std::string> const& serviceList, bool verbose, bool number)
{
  for (unsigned int i = 0; i < serviceList.size(); ++i)
  {
    if (isNumber(serviceList[i]))
      showServiceInfo(::atoi(serviceList[i].c_str()), verbose, number);
    else
      this->showServiceInfo(serviceList[i], verbose, number);
    if (verbose)
      if (i + 1 != serviceList.size())
        std::cout << "========================================================================" << std::endl;
  }
}

void SessionHelper::showServicesInfo(bool verbose, bool number)
{
  std::vector<qi::ServiceInfo> servs = _session.services();

  for (unsigned int i = 0; i < servs.size(); ++i)
  {
    this->_showServiceInfo(servs[i], verbose);
    if (verbose)
      if (i + 1 != servs.size())
        std::cout << "========================================================================" << std::endl;
  }
}

qi::FutureSync<void> SessionHelper::connect(const qi::Url &serviceDirectoryURL)
{
  return _session.connect(serviceDirectoryURL);
}

qi::FutureSync<void> SessionHelper::close()
{
  return _session.close();
}

qi::FutureSync< qi::ObjectPtr > SessionHelper::service(const std::string &service, const std::string &protocol)
{
  return _session.service(service, protocol);
}

qi::FutureSync< std::vector<qi::ServiceInfo> > SessionHelper::services(qi::Session::ServiceLocality locality)
{
  return _session.services(locality);
}