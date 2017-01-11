#include <iostream>
#include <array>
#include <memory>
#include <algorithm>
#include <cctype>
#include <string>

namespace API
{
   struct Command
   {
      virtual ~Command() = default;
      
      virtual void execute(std::ostream&) = 0;
   };
}

namespace Concrete
{
   struct ReadCommand : public API::Command
   {
      void execute(std::ostream& os) override { os << "read\n"; }
   };

   struct WriteCommand : public API::Command
   {
      void execute(std::ostream& os) override { os << "write\n"; }
   };

   struct ComplexCommand : public API::Command
   {
      ComplexCommand(std::string text) : m_text() 
	  { 
		  std::transform(text.begin(), text.end(), std::back_inserter(m_text), [](std::string::value_type c)
		  {  return std::toupper(c); });
	  }
      
      void execute(std::ostream& os) override { os << m_text << '\n'; }
      
   private:
      std::string m_text;
   };
}

int main( int argc, char** argv )
{
   std::array<std::unique_ptr< API::Command >, 5> const commands = 
   { 
       std::make_unique< Concrete::ReadCommand >()
      ,std::make_unique< Concrete::WriteCommand >()
      ,std::make_unique< Concrete::ComplexCommand >("blub")
      ,std::make_unique< Concrete::ReadCommand >()
      ,std::make_unique< Concrete::ReadCommand >()
   };
 
   /** Somewhere else, nobody knows about concrete commands,
    *  they look all the same.
    */
   for ( auto& command : commands ) { command->execute(std::cout); }; ///< Execute all in unified way
}
