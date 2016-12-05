#include "Processor.h"

int main( int argc, char** argv )
{
   using namespace API;

   Processor* p( new Processor() );
   p->Print();

   return 0;
}

