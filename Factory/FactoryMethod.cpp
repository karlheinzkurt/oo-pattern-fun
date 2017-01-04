#include "FactoryMethod.h"

namespace Concrete
{   
   std::string Product::toString() const 
   {  return "product"; }
      
   std::unique_ptr<Product> Product::create()
   {
      /** We decide what type of object we deliver,
       *  here we return a hidden special implementation.
       */
      struct SpecialProduct : Product
      {
         virtual std::string toString() const { return std::string("special ") + Product::toString(); }
      };
      
      return std::make_unique<SpecialProduct>();
   }
}
