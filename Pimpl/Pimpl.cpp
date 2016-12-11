#include "Processor.h"

/** No dependencies to stuff used by Processor 
 */

int main( int argc, char** argv )
{
   using namespace API;

   Processor* p( new Processor() );
   p->print();

   return 0;
}
