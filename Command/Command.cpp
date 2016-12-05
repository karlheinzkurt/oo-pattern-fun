#include <iostream>
#include <array>
#include <memory>
#include <algorithm>

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
   typedef std::array< std::unique_ptr< API::Command >, 3 > CommandListType;
   CommandListType const commands = 
   { 
       std::make_unique< Concrete::ReadCommand >()
      ,std::make_unique< Concrete::WriteCommand >()
      ,std::make_unique< Concrete::ComplexCommand >()
   };

   std::for_each( commands.begin(), commands.end(), []( CommandListType::value_type const& command )
   {  command->execute(); } );
}

