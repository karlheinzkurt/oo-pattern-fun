#pragma once

#include <string>
#include <memory>

namespace Concrete
{
   struct Product
   {  
      virtual ~Product() = default;
      
      virtual std::string toString() const = 0;
      
      /** This is not the factory method like described in GoF
       *  but it is quite popular.
       */
      static std::unique_ptr<Product> create();
   };
}
