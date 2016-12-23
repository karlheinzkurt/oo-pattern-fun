#include "Processor.h"

#include <memory>

/** No dependencies to stuff used by Processor 
 */

int main( int argc, char** argv )
{
   auto processor(std::make_unique<Concrete::Processor>("bla"));
   processor->print();
}
