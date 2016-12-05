#include <iostream>
#include <vector>
#include <exception>

namespace API
{
   class VisitorBase
   {
      public:
      virtual ~VisitorBase() {}
      
      friend std::ostream& operator<<( std::ostream& os, VisitorBase const& v )
      {  v.print( os ); return os; }
      
      private:
      virtual void print( std::ostream& ) const = 0;
   };

   template < class ElementType >
   class Visitor : virtual public VisitorBase
   {
      public:
      virtual ~Visitor() {}
      virtual void visit( ElementType* ) = 0;
   };   

   class ElementBase
   {
      public:
      virtual ~ElementBase() {}
      virtual void accept( VisitorBase* const v ) = 0;
   };

   class VisitorElementMismatchException : public virtual std::exception
   {
      public:
      char const* what() const throw()
      {  
         static char const* msg( "visitor not matching element" ); 
         return msg;
      }
   };

   template < class ElementType >
   class Element : public ElementBase
   {
      public:
      virtual ~Element() {}
      virtual void accept( VisitorBase* const v )
      { 
         typedef Visitor< ElementType > VisitorType;
         
         VisitorType* _v( dynamic_cast< Visitor< ElementType >* >( v ) );
         ElementType* _e( dynamic_cast< ElementType* >( this ) );
         
         if ( _v == NULL || _e == NULL )
         {  throw VisitorElementMismatchException(); }

         _v->visit( _e );
      }
   };
}

namespace Concrete
{
   class Accomodation : public API::Element< Accomodation >
   { public: int getPrice() const { return 180; } };

   class Traveling : public API::Element< Traveling >
   { public: int getPrice() const { return 250; } };

   class AdditionalCosts : public API::Element< AdditionalCosts >
   { public: int getPrice() const { return 65; } };

   class PriceVisitor : public API::Visitor< Accomodation >, public API::Visitor< Traveling >, public API::Visitor< AdditionalCosts >
   {
      private:
      int m_price;

      public:
      PriceVisitor() : m_price( 0 ) {}

      void visit( Concrete::Accomodation* a )
      {  m_price += a->getPrice(); }

      void visit( Concrete::Traveling* t )
      {  m_price += t->getPrice() * 2 /* to and back */; }

      void visit( Concrete::AdditionalCosts* ac )
      {  m_price += ac->getPrice(); }   

      void print( std::ostream& os ) const 
      {  os << "Price: " << m_price; }
   };

   class KillVisitor : public API::Visitor< Accomodation >, public API::Visitor< Traveling >, public API::Visitor< AdditionalCosts >
   {
      private:
      int m_count;

      public:
      KillVisitor() : m_count( 0 ) {}

      void visit( Concrete::Accomodation* a )
      {  delete a; ++m_count; }

      void visit( Concrete::Traveling* t )
      {  delete t; ++m_count; }

      void visit( Concrete::AdditionalCosts* ac )
      {  delete ac; ++m_count; }

      void print( std::ostream& os ) const 
      {  os << "Killed: " << m_count; }
   };
}

int main( int argc, char** argv )
{
   typedef std::vector< API::ElementBase* > TElements;
   typedef std::vector< API::VisitorBase* > TVisitors;

   TElements elements = { new Concrete::Accomodation, new Concrete::Traveling, new Concrete::AdditionalCosts };
   TVisitors visitors = { new Concrete::PriceVisitor, new Concrete::KillVisitor };

   const TElements::const_iterator ee( elements.end() );
   for ( TElements::const_iterator ec( elements.begin() ); ec != ee; ++ec )
   {  
      const TVisitors::const_iterator ve( visitors.end() );
      for ( TVisitors::const_iterator vc( visitors.begin() ); vc != ve; ++vc )
      {  (*ec)->accept( *vc ); }
   } 

   std::cout << ( *visitors[0] ) << std::endl << ( *visitors[1] ) << std::endl;
   delete visitors[0], delete visitors[1];
   return 0;
}
