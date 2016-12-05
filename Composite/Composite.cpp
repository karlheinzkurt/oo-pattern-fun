#include <iostream>
#include <set>

namespace API
{
   class Graphic
   {
      public:
      virtual ~Graphic() {}

      virtual void print() const = 0;  
   };
}

namespace Concrete
{
   class Ellipse : public API::Graphic
   {
      public:
      void print() const
      {  std::cout << "ellipse" << std::endl; }  
   };

   class Rectangle : public API::Graphic
   {
      public:
      void print() const
      {  std::cout << "rectangle" << std::endl; }  
   };

   class GraphicComposite : public API::Graphic
   {
      private:
      typedef std::set< API::Graphic* > GraphicType;
      GraphicType m_childs;   

      public:
      ~GraphicComposite()
      {
         GraphicType::iterator const ge( m_childs.end() );
         for ( GraphicType::iterator gc( m_childs.begin() ); gc != ge; ++gc )
         {  delete *gc; }         
      }
   
      void print() const
      {  
         std::set< API::Graphic* >::const_iterator const ce( m_childs.end() );
         for ( std::set< API::Graphic* >::const_iterator cc( m_childs.begin() ); cc != ce; ++cc )
         {  (*cc)->print(); }
      }

      void add( API::Graphic* const g )
      {  m_childs.insert( g ); }

      void remove( API::Graphic* const g )
      {  m_childs.erase( g ); }
   };
}

int main( int argc, char** argv )
{
   Concrete::GraphicComposite* container( new Concrete::GraphicComposite );
   for ( unsigned int i = 0; i < 3; ++i )
   {
      Concrete::GraphicComposite* subContainer( new Concrete::GraphicComposite );
      subContainer->add( new Concrete::Rectangle );
      subContainer->add( new Concrete::Ellipse );
      container->add( subContainer );
   }
   container->add( new Concrete::Ellipse );   
   container->add( new Concrete::Rectangle );   

   container->print();
   delete container;
   return 0;
}
