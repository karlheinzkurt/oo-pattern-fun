#include <iostream>
#include <string>
#include <map>

namespace API
{
   class State
   {  public:
      virtual ~State() {}
      virtual void execute( char const ) = 0;
   };
}

namespace Concrete
{
   class NormalState : public API::State
   {  public:
      void execute( char const ch )
      {  std::cout << ch; }

      static char key()
      {  static char k( '.' ); return k; }
   };

   class LowerState : public API::State
   {  public:
      void execute( char const ch )
      {  std::cout << (char)( ch - ( ( ch >= 'A' && ch <= 'Z' ) ? ( 'A' - 'a' ) : 0 ) ); }

      static char key()
      {  static char k( '-' ); return k; }
   };

   class UpperState : public API::State
   {  public:
      void execute( char const ch )
      {  std::cout << (char)( ch + ( ( ch >= 'a' && ch <= 'z' ) ? ( 'A' - 'a' ) : 0 ) ); }

      static char key()
      {  static char k( '+' ); return k; }
   };

   class Processor
   {
      typedef std::map< char const, API::State* > TStates;

      public:
      Processor()
      {
         m_states[ UpperState::key() ] = new UpperState;
         m_states[ LowerState::key() ] = new LowerState;
         m_states[ NormalState::key() ] = new NormalState;
         m_state = m_states[ '.' ]; 
      }

      ~Processor()
      {
         TStates::iterator const se( m_states.end() );
         for ( TStates::iterator sc( m_states.begin() ); sc != se; ++sc )
         {  delete (*sc).second; }
      }

      void process( std::string const& phrase ) 
      {
         std::string::const_iterator const se( phrase.end() );
         for ( std::string::const_iterator sb( phrase.begin() ); sb != se; ++sb )
         {
            char const& ch( *sb );
            switch ( ch )
            {
               case '+': 
               case '-':
               case '.':
               m_state = m_states[ ch ];  continue;
               default:                   break;
            }

            m_state->execute( ch );
         }
      }

      private:
      API::State*  m_state;
      TStates      m_states;   
   };
}

int main( int argc, char** argv )
{
   Concrete::Processor processor;   

   std::string line;
   while ( std::getline( std::cin, line ) )
   {  processor.process( line ); }
}

