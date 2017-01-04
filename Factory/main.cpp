
#include "AbstractFactory.h"
#include "FactoryMethod.h"

#include <iostream>

int main( int argc, char** argv )
{   
   /** To be able to control here what kind of object is 
       created inside some object.
    */
   {
      Concrete::ComplexCalculator calculator( std::make_unique< Concrete::MultiplyFactory >() );
      std::cout << calculator.calculate( 5, 23 ) << '\n';
   }
   {
      Concrete::ComplexCalculator calculator( std::make_unique< Concrete::AddFactory >() );
      std::cout << calculator.calculate( 5, 23 ) << '\n';
   }

   /** Let implementation decide what kind of object is 
    *  created.
    */
   {
      auto product(Concrete::Product::create());
      std::cout << product->toString() << '\n';
   }
}
