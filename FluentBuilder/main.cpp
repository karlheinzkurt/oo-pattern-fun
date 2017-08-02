
#include "ClassBuild.h"
#include "FunctionParameterBuild.h"

int main( int argc, char** argv )
{
   /** Don't care about the order of the arguments 
    */
   {
      auto element(Element::Config().withLength( 20 ).done());
      std::cout << element << '\n';
   }
   {
      auto element(Element::Config().withWidth( 30 ).withHeight( 15 ).done());
      std::cout << element << '\n';
   }
   {
      auto element(Element::Config().withHeight( 30 ).withLength( 15 ).withWidth( 3 ).done());
      std::cout << element << '\n';
   }
   
   /** Using builder to avoid confusing function parameters
    *  - No need to change signature when parameters are added
    *  - Don't care about order
    */
   {
      print(Error::Config().withType(5).withReturnValue(23).onLocation(__FUNCTION__, __LINE__));
   }
}