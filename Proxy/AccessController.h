#pragma once

#include <set>
#include <string>

namespace API
{
   struct AccessController
   {
      virtual ~AccessController() = default;
      
      virtual bool isAuthorized(std::string user) const = 0;
   };
}

namespace Concrete
{
   struct AccessController : API::AccessController
   {
      AccessController(std::set<std::string> authorizedUsers) : m_authorizedUsers(std::move(authorizedUsers)) 
      {}
      
      virtual bool isAuthorized(std::string user) const override
      {  return m_authorizedUsers.find(user) != m_authorizedUsers.end(); }
      
   private:
      std::set<std::string> m_authorizedUsers;
   };   
}
