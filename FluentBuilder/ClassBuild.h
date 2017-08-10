#include <memory>
#include <iostream>

struct Element
{
   struct Config
   {
      Config() : m_length( 0 ), m_width( 0 ), m_height( 0 ) {}

      Config& withLength( int const l )
      {  m_length = l;  return *this; }

      Config& withWidth( int const w )
      {  m_width = w; return *this; }

      Config& withHeight( int const h )      
      {  m_height = h; return *this; }

      Element done() const
      {
         /** Add validation checks here
          */
         return Element( *this ); 
      } 
      
      friend std::ostream& operator<<( std::ostream& os, Config const& c )
      {  return ( os << "Length: " << c.m_length << ", Width: " << c.m_width << ", Height: " << c.m_height ); }

   private:
      int m_length;
      int m_width;
      int m_height;

      friend struct Element; ///< \todo Avoid friend here
   };

   Element(Config c) : m_config(c) {}    

   Element() = delete;
   Element(Element const&) = delete;
   Element& operator=(Element const&) = delete;
   Element(Element&&) = default;
   Element& operator=(Element&&) = default;

   friend std::ostream& operator<<( std::ostream& os, Element const& e ) { return os << e.m_config; }

private:
   Config m_config;
};
