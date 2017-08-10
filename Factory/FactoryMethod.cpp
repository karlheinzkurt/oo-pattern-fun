#include "FactoryMethod.h"

namespace Concrete
{   
   std::unique_ptr<Product> Product::create()
   {
      /** We decide what type of object we deliver,
       *  here we return a hidden special implementation.
       */
      struct SpecialProduct : Product
      {
         virtual std::string toString() const override 
         {  return std::string("special hidden product"); }
      };
      
      return std::make_unique<SpecialProduct>();
   }
}
