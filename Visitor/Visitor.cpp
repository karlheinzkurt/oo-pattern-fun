#include <iostream>
#include <string>
#include <vector>
#include <exception>
#include <memory>

namespace API
{
   struct VisitorBase
   {
      virtual ~VisitorBase() {}
      
      virtual std::string toString() const = 0;
   };

   template < class ElementType >
   struct Visitor : virtual public VisitorBase
   {
      virtual ~Visitor() {}
      
      virtual void visit( ElementType& ) = 0;
   };   

   struct ElementBase
   {
      virtual ~ElementBase() {}
      
      virtual void accept( VisitorBase& ) = 0;
   };

   template < class ElementType >
   struct Element : public ElementBase
   {
      virtual ~Element() {}
      
      virtual void accept( VisitorBase& v ) override
      {         
         auto& _v( dynamic_cast< Visitor< ElementType >& >( v ) );
         auto& _e( dynamic_cast< ElementType& >( *this ) );
         _v.visit( _e );
      }
   };
   
   std::ostream& operator<<( std::ostream& os, VisitorBase const& v )
   {  return os << v.toString(); }
}

namespace Concrete
{
   struct Accomodation : public API::Element< Accomodation >
   { 
      int getPrice() const { return 180; }
   };

   struct Traveling : public API::Element< Traveling >
   {  
      int getPrice() const { return 250; } 
   };

   struct AdditionalCosts : public API::Element< AdditionalCosts >
   {  
      int getPrice() const { return 65; }
   };

   struct PriceVisitor : public API::Visitor< Accomodation >, public API::Visitor< Traveling >, public API::Visitor< AdditionalCosts >
   {
      PriceVisitor() : m_price( 0 ) {}

      void visit( Concrete::Accomodation& a ) override
      {  m_price += a.getPrice(); }

      void visit( Concrete::Traveling& t ) override
      {  m_price += t.getPrice() * 2 /* to and back */; }

      void visit( Concrete::AdditionalCosts& ac ) override
      {  m_price += ac.getPrice(); }

      std::string toString() const override
      {  return std::string("Price: ") + std::to_string(m_price); }
      
   private:
      int m_price;
   };
   
   /** \todo Add another visitor for something different than price
    * */
}

int main( int argc, char** argv )
{
   std::vector<std::unique_ptr<API::ElementBase>> elements;
   elements.emplace_back(std::make_unique<Concrete::Accomodation>());
   elements.emplace_back(std::make_unique<Concrete::Traveling>());
   elements.emplace_back(std::make_unique<Concrete::AdditionalCosts>());
   
   std::vector<std::unique_ptr<API::VisitorBase>> visitors;
   visitors.emplace_back(std::make_unique<Concrete::PriceVisitor>());

   for ( auto& element : elements )
   {  
      for ( auto const& visitor : visitors )
      {  element->accept( *visitor ); }
   } 

   for ( auto const& visitor : visitors )
   {  std::cout << *visitor << '\n'; }
   
   return 0;
}
