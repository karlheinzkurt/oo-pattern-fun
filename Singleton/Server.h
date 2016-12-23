#pragma once

#include <iosfwd>

namespace Concrete
{
   struct Server
   {
      static Server& getInstance();
   
      void run(std::ostream&, size_t id);

   private:
      Server(size_t instance);
      
      /** No copy or move, it's a highlander, there's exactly one and it's excactly here
       */
      Server(Server&&) = delete;
      Server& operator=(Server&&) = delete;
      Server(Server const&) = delete;
      Server& operator=(Server const&) = delete;
      
      size_t m_instance;
   };
}
