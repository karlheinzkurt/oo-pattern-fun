#include "Server.h"

#include <iostream>
#include <memory>
#include <atomic>

namespace
{
   std::unique_ptr<Concrete::Server> s_instance;
   std::atomic<size_t> s_instanceCount;
}

namespace Concrete
{
   Server& Server::getInstance() 
   {  
      static Concrete::Server* server = [&] // Should be fine since C++11 
      { 
         s_instance.reset(new Server(s_instanceCount++));
         return s_instance.get();
      }();
      return *server;
   }

   Server::Server(size_t instanceCount) : m_instanceCount(instanceCount) {}

   void Server::run(std::ostream& os, size_t id)
   {  os << "Server instance " << m_instanceCount << " is running " << id << '\n'; }
}
