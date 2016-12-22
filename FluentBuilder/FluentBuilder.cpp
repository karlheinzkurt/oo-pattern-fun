#include <memory>
#include <iostream>

struct Element
{
   struct Builder
   {
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

      friend class Element; ///< \todo Avoid friend here
   };

   Element( Builder const& b ) :
       m_length( b.m_length )
      ,m_width( b.m_width )
      ,m_height( b.m_height )
   {}    

   Element() = delete;
   Element(Element const&) = delete;
   Element& operator=(Element const&) = delete;
   Element(Element&&) = default;
   Element& operator=(Element&&) = default;

   friend std::ostream& operator<<( std::ostream& os, Element const& e )
   {  return ( os << "Length: " << e.m_length << ", Width: " << e.m_width << ", Height: " << e.m_height ); }

private:
   int m_length;
   int m_width;
   int m_height;
};

int main( int argc, char** argv )
{
   {
      auto element(Element::Builder().withLength( 20 ).withWidth( 30 ).build());
      std::cout << element << '\n';
   }
   {
      auto element(Element::Builder().withWidth( 30 ).withHeight( 15 ).build());
      std::cout << element << '\n';
   }
   {
      auto element(Element::Builder().withHeight( 30 ).withLength( 15 ).withWidth( 3 ).build());
      std::cout << element << '\n';
   }
}
