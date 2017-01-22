#pragma once

#include <ostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <sstream>

namespace API
{
   struct Graphic
   {
      virtual ~Graphic() = default;
      
      virtual std::string toString() const = 0;  
   };
   
   bool operator==(Graphic const& a, Graphic const& b)
   {  return a.toString().compare(b.toString()) == 0; }
   
   std::ostream& operator<<(std::ostream& os, Graphic const& g)
   {  return os << g.toString(); }
}

namespace Concrete
{
   struct Circle : public API::Graphic
   {
      Circle(unsigned int radius) : m_radius(radius) {}
      
      std::tuple<unsigned int, unsigned int> getDimension() const
      { 
         
      }
      
      
      std::string toString() const override
      {  
               
      }
      
   private:
      unsigned int m_radius;
   };

   struct Rectangle : public API::Graphic
   {
      std::string toString() const override
      {  return "rectangle"; }
   };

   struct GraphicComposite : public API::Graphic
   {   
      typedef std::vector<std::unique_ptr<API::Graphic>> GraphicCollectionType;
      
      GraphicComposite() : m_indent(0), m_childs() {}
      GraphicComposite(GraphicComposite&&) = default;
      GraphicComposite& operator=(GraphicComposite&&) = default;
      
      std::string toString() const override
      {  
         std::ostringstream os;
         for ( auto const& c : m_childs )
         { os << std::string(m_indent, ' ') << c->toString() << '\n'; }
         return os.str();
      }

      GraphicComposite& addSubGraphic() ///< Just to avoid publishing the indent stuff to user
      {  
         std::unique_ptr<GraphicComposite> sub(new GraphicComposite(m_indent + 3));
         auto& reference(*sub);
         add(std::move(sub));
         return reference;
      }
      
      void add(std::unique_ptr<API::Graphic> g)
      {  m_childs.emplace_back(std::move(g)); }
      
      void remove(API::Graphic const& g)
      {  
         std::remove_if(m_childs.begin(), m_childs.end(), [&](GraphicCollectionType::value_type const& c)
         {  return *c == g; });  
      }
            
   private:
      GraphicComposite(size_t indent) : m_indent(indent), m_childs() {}
   
      size_t m_indent;
      GraphicCollectionType m_childs;
   };
}
