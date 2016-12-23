#include "Server.h"

#include <iostream>
#include <memory>
#include <atomic>

namespace
{
   std::unique_ptr<Concrete::Server> instance;
   std::atomic<size_t> instanceCount;
}

namespace Concrete
{
   Server& Server::getInstance() 
   {  
      static Concrete::Server* server = [&] // Should be fine since C++11 
      { 
         instance.reset(new Server(instanceCount++));
         return instance.get();
      }();
      return *server;
   }

   Server::Server(size_t instance) : m_instance(instance) {}

   void Server::run(std::ostream& os, size_t id)
   {  os << "Server " << m_instance << " is running " << id << '\n'; }
}
