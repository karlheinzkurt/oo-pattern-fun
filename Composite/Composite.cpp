#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <sstream>

namespace API
{
   struct Graphic
   {
      virtual ~Graphic() {}
      
      virtual std::string toString() const = 0;  
   };
   
   bool operator==(Graphic const& a, Graphic const& b)
   {  return a.toString().compare(b.toString()) == 0; }
}

namespace Concrete
{
   struct Ellipse : public API::Graphic
   {
      std::string toString() const override
      {  return "ellipse\n"; }  
   };

   struct Rectangle : public API::Graphic
   {
      std::string toString() const override
      {  return "rectangle\n"; }  
   };

   struct GraphicComposite : public API::Graphic
   {   
      std::string toString() const override
      {  
         std::ostringstream os;
         for ( auto const& c : m_childs ) { os << c->toString(); }
         return os.str();
      }

      void add(std::unique_ptr<API::Graphic> g)
      {  m_childs.emplace_back(std::move(g)); }

      void remove(API::Graphic const& g)
      {  
         std::remove_if(m_childs.begin(), m_childs.end(), [&](GraphicType::value_type const& c)
         {  return *c == g; });  
      }
      
   private:
      typedef std::vector<std::unique_ptr<API::Graphic>> GraphicType;
      GraphicType m_childs;
   };
}

int main( int argc, char** argv )
{
   auto container(std::make_unique<Concrete::GraphicComposite>());
   for ( unsigned int i = 0; i < 3; ++i )
   {
      auto subContainer(std::make_unique<Concrete::GraphicComposite>());
      subContainer->add(std::make_unique<Concrete::Rectangle>());
      subContainer->add(std::make_unique<Concrete::Ellipse>());
      container->add(std::move(subContainer));
   }
   container->add(std::make_unique<Concrete::Ellipse>());   
   container->add(std::make_unique<Concrete::Rectangle>());   

   std::cout << container->toString();
   return 0;
}
