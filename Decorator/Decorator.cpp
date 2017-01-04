#include <iostream>
#include <memory>
#include <sstream>

namespace API
{
   struct TextInterface
   {
      virtual ~TextInterface() {}
      
      virtual void setText(std::string text) = 0;

      virtual std::string toString() const = 0;
   };
   
   std::ostream& operator<<( std::ostream& os, TextInterface const& text )
   {  return os << text.toString(); }
} // API

namespace Concrete
{
   struct TextObject : public API::TextInterface
   {
      TextObject( std::string const& text ) : m_text( text ) {}

      virtual void setText(std::string text) override
      {  m_text = text; }

      virtual std::string toString() const override
      {  return m_text; }

   private:
      std::string m_text;
   };

   struct PipeDecorator : public API::TextInterface
   {
      PipeDecorator( std::unique_ptr<API::TextInterface> decoratee ) : m_decoratee(std::move(decoratee)) {} 

      virtual void setText(std::string text) override
      {  m_decoratee->setText(text); }

      virtual std::string toString() const override
      {  
         std::ostringstream os;
         os << "|"  << m_decoratee->toString() << "|";
         return os.str();
      }
      
   private:
      std::unique_ptr<API::TextInterface> m_decoratee;
   };
   
   struct MinusDecorator : public API::TextInterface
   {
      MinusDecorator( std::unique_ptr<API::TextInterface> decoratee ) : m_decoratee(std::move(decoratee)) {} 

      virtual void setText(std::string text) override
      {  m_decoratee->setText(text); }

      virtual std::string toString() const override
      {  
         std::ostringstream os;
         os << "-"  << m_decoratee->toString() << "-";
         return os.str();
      }
      
   private:
      std::unique_ptr<API::TextInterface> m_decoratee;
   };
} // Concrete

int main( int argc, char** argv )
{
   using namespace Concrete;

   /** Original object and decorated object have the same interface,
    *  so we can re-assign the decorated object to the same pointer.
    */

   std::unique_ptr<API::TextInterface> text(new TextObject("some text"));
   std::cout << *text << '\n';
   
   text = std::make_unique<PipeDecorator>(std::make_unique<MinusDecorator>(std::make_unique<PipeDecorator>(std::move(text))));
   std::cout << *text << '\n';
   
   text->setText("blub");
   std::cout << *text << '\n';
}

