
#include "Server.h"

#include <iostream>
#include <thread>
#include <vector>

int main( int argc, char** argv )
{   
   /** Let's run it by 100 threads in parallel
    */
    
   std::vector<std::thread> threads;
   for (size_t t(0); t < 100; ++t)
   {
      threads.emplace_back(std::thread([t]
      {  Concrete::Server::getInstance().run(std::cout, t); }));
   }
   for (auto& t : threads) { t.join(); }
}
