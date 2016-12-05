#include <memory>
#include <iostream>

class Element
{
   public:
   class Builder
   {
      public:
      Builder() : m_length( 0 ), m_width( 0 ), m_height( 0 ) {}

      Builder& withLength( int const l )
      {  m_length = l;  return *this; }

      Builder& withWidth( int const w )
      {  m_width = w; return *this; }

      Builder& withHeight( int const h )      
      {  m_height = h; return *this; }

      Element build() const
      {  return Element( *this ); } 

      private:
      int m_length;
      int m_width;
      int m_height;

      friend class Element;
   };

   Element( Builder const& b ) :
       m_length( b.m_length )
      ,m_width( b.m_width )
      ,m_height( b.m_height )
   {}    

   Element& operator=( Builder const& b )
   {
      m_length = b.m_length;
      m_width = b.m_width; 
      m_height = b.m_height;
      return (*this);
   }

   friend std::ostream& operator<<( std::ostream& os, Element const& e )
   {  return ( os << e.m_length << "x" << e.m_width << "x" << e.m_height ); }

   private:
   int m_length;
   int m_width;
   int m_height;
};

int main( int argc, char** argv )
{
   Element element( Element::Builder().withLength( 20 ).withWidth( 30 ).build() );
   std::unique_ptr< Element > p_element( new Element( Element::Builder().withWidth( 10 ).withHeight( 15 ).build() ) );
   std::cout << element << " - " << (*p_element) << std::endl;
   return 0;
}

