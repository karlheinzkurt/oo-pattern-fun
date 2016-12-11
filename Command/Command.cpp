#include <iostream>
#include <array>
#include <memory>

#include <boost/algorithm/string.hpp>

namespace API
{
   struct Command
   {
      virtual ~Command() {}
      
      virtual void execute() = 0;
   };
}
namespace Concrete
{
   struct ReadCommand : public API::Command
   {
      void execute() override { std::cout << "read\n"; }
   };

   struct WriteCommand : public API::Command
   {
      void execute() override { std::cout << "write\n"; }
   };

   struct ComplexCommand : public API::Command
   {
      void execute() override
      {
         std::string userInput;
         std::getline( std::cin, userInput );
         boost::to_upper( userInput );
         std::cout << userInput;
      }
   };
}

int main( int argc, char** argv )
{
   std::array< std::unique_ptr< API::Command >, 4 > const commands = 
   { 
       std::make_unique< Concrete::ReadCommand >()
      ,std::make_unique< Concrete::WriteCommand >()
      ,std::make_unique< Concrete::ComplexCommand >()
      ,std::make_unique< Concrete::ReadCommand >()
   };

   for ( auto& command : commands ) { command->execute(); }; ///< Execute all in unified way
}
