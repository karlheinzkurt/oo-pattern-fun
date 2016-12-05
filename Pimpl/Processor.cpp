#include <iostream>
#include <string>
#include "Processor.h"

namespace API
{
   struct Processor::PrivateProcessor
   {
      PrivateProcessor( const std::string& t ) : m_Text( t ) {}
      std::string m_Text;
   };

   Processor::Processor() : m_p( new PrivateProcessor( "bla" ) ) {}

   Processor::~Processor() { delete m_p; }

   void Processor::Print( void ) const
   {  std::cout << m_p->m_Text << std::endl; }
}

