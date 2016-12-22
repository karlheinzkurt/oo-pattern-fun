
#include <iostream>
#include <memory>
#include <mutex>

struct Server
{
      static Server& getInstance();
   
      void run();

   private:
      Server() = default;
      Server(Server&&) = default;
      Server& operator=(Server&&) = default;
      
      Server(Server const&) = delete;
      Server& operator=(Server const&) = delete;
};

namespace
{
   std::unique_ptr<Server> instance;
   std::once_flag onceFlag;
}

Server& Server::getInstance() 
{  
   std::call_once(onceFlag, []
   {
      instance.reset(new Server);
   });
   return *instance.get();
}

void Server::run()
{  std::cout << "Server" << std::endl; }
   
int main( int argc, char** argv )
{   
   auto& server(Server::getInstance());
   server.run();
}
