#include <iostream>
#include <string>
#include "Processor.h"

namespace Concrete
{
   struct Processor::Impl
   {
      Impl(std::string const& text) : m_text(text) {}
      
      std::string m_text;
   };

   Processor::Processor(char const* const text) : m_pimpl(new Impl(text)) {}

   Processor::~Processor() { delete m_pimpl; }

   void Processor::print() const
   {  std::cout << m_pimpl->m_text << '\n'; }
}

