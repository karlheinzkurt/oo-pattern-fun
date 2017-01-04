#pragma once

#include <string>
#include <memory>

namespace Concrete
{
   struct Product
   {  
      virtual std::string toString() const;
      
      /** This is not the factory method like described in GoF
       *  but it is quite popular.
       */
      static std::unique_ptr<Product> create();
      
   private:
      Product() = default; ///< Private, use factory method to create a product
   };
}
