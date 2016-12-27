#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include <memory>
#include <cctype>

namespace API
{
   struct State
   {
      virtual ~State() {}
      
      virtual char execute( char const ) = 0;
   };
}

namespace Concrete
{
   struct NormalState : public API::State
   {
      virtual char execute( char const ch ) override
      {  return ch; }

      static char key() { return '.'; }
   };

   struct LowerState : public API::State
   {
      virtual char execute( char const ch ) override
      {  return std::tolower(ch); }

      static char key() { return '-'; }
   };

   struct UpperState : public API::State
   {
      virtual char execute( char const ch ) override
      {  return std::toupper(ch); }

      static char key() { return '+'; }
   };

   struct Processor
   {
      typedef std::map<char const, std::unique_ptr<API::State>> StateMapType;

      Processor()
      {
         m_states.emplace(StateMapType::value_type(UpperState::key(), std::make_unique<UpperState>()));
         m_states.emplace(StateMapType::value_type(LowerState::key(), std::make_unique<LowerState>()));
         m_states.emplace(StateMapType::value_type(NormalState::key(), std::make_unique<NormalState>()));
         m_state = m_states.at(NormalState::key()).get(); 
      }

      std::string process(std::string const& phrase)
      {
         std::ostringstream result;
         for (auto const character : phrase)
         {
            switch (character) ///< This characters will switch the state
            {
               case '+': 
               case '-':
               case '.':
               m_state = m_states.at(character).get(); continue;
               default: break;
            }
            result << m_state->execute(character);
         }
         return result.str();
      }

   private:
      StateMapType m_states;   
      API::State* m_state;
   };
}

int main( int argc, char** argv )
{
   Concrete::Processor processor;   

   std::string line;
   while ( std::getline( std::cin, line ) )
   {  std::cout << processor.process( line ) << '\n'; }
}
