#include <iostream>
#include <string>
#include "Processor.h"

namespace API
{
   struct Processor::Impl
   {
      Impl(std::string const& t ) : m_text( t ) {}
      
      std::string m_text;
   };

   Processor::Processor() : m_pimpl( new Impl( "bla" ) ) {}

   Processor::~Processor() { delete m_pimpl; }

   void Processor::print() const
   {  std::cout << m_pimpl->m_text << '\n'; }
}

