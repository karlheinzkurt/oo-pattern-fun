#include <iostream>

namespace API
{
   class TextInterface
   {
      public:
      virtual ~TextInterface() {}

      virtual std::ostream& Print( std::ostream& ) const = 0;
      
      friend std::ostream& operator<<( std::ostream& os, const TextInterface& Text )
      {  return ( Text.Print( os ) ); }
   };

   class TextDecorator : public TextInterface
   {
      public:
      TextDecorator( TextInterface* i ) : m_Component( i ) { }
      virtual ~TextDecorator() { delete m_Component; }
    
      virtual std::ostream& Print( std::ostream& os ) const
      {  return ( m_Component->Print( os ) ); } 

      private:
      TextInterface* m_Component;
   };
} // API

namespace Concrete
{
   class TextObject : public API::TextInterface
   {
      public:
      TextObject( const std::string& Text ) : m_Text( Text ) { }

      std::ostream& Print( std::ostream& os ) const
      {  return ( os << m_Text ); }

      private:
      std::string m_Text;
   };

   class PipeDecorator : public API::TextDecorator
   {
      public:
      PipeDecorator( API::TextInterface* i ) : API::TextDecorator( i ) { } 

      std::ostream& Print( std::ostream& os ) const
      {  
         os << "|";
         API::TextDecorator::Print( os );
         return ( os << "|" );          
      }
   };
} // Concrete

int main( int argc, char** argv )
{
   using namespace Concrete;

   API::TextInterface* Text = new PipeDecorator( new PipeDecorator( new TextObject( "some text" ) ) );
   std::cout << ( *Text );
   delete Text;
   return 0;
}

