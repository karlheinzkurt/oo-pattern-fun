#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <memory>

namespace API
{
   /** We do need this forward declarations :-(,
       because the visitor has to know this elements.
    */
   struct Accomodation;
   struct Traveling;
   struct Fun;
   
   /** Abstract visitor has to be extended 
       when elements are increasing :-(
    */
   struct Visitor
   {
      virtual ~Visitor() {}      
      virtual void visit(Accomodation&) = 0;
      virtual void visit(Traveling&) = 0;
      virtual void visit(Fun&) = 0;
      virtual std::string toString() const = 0;
   };
   
   std::ostream& operator<<(std::ostream& os, Visitor& v)
   {  return os << v.toString(); }

   struct Element
   {
      virtual ~Element() = default;  
      virtual void accept(Visitor&) = 0;
   };
   
   struct Accomodation
   { 
      virtual int getPrice() const = 0;
      virtual int getStars() const = 0;
   };

   struct Traveling
   {  
      virtual int getPrice() const = 0;
      virtual int getDistance() const = 0;
      virtual int getClass() const = 0;
   };

   struct Fun
   {  
      virtual int getPrice() const = 0;
      virtual int getRelaxFactor() const = 0;
   };   
}

namespace Concrete
{
   struct Cruise : API::Element, API::Accomodation, API::Traveling, API::Fun
   {
      virtual void accept(API::Visitor& v) override 
      { 
         v.visit(static_cast<API::Accomodation&>(*this));
         v.visit(static_cast<API::Traveling&>(*this));
         v.visit(static_cast<API::Fun&>(*this));
      } 
      virtual int getPrice() const { return 2500 / 3; } ///< Hmm, gets called 3 times, this is stupid
      virtual int getStars() const { return 4; }
      virtual int getDistance() const { return 1200; }
      virtual int getClass() const { return 2; }
      virtual int getRelaxFactor() const { return 3; }
   };
   
   struct Flight : API::Element, API::Traveling
   {
      Flight(int _class) : m_class(_class) {}
      virtual void accept(API::Visitor& v) override { v.visit(*this); } 
      virtual int getPrice() const { return 1000; }
      virtual int getClass() const { return m_class; }
      virtual int getDistance() const { return 320; }
      
   private:
      int m_class;
   };
   
   struct Hotel : API::Element, API::Accomodation
   {
      virtual void accept(API::Visitor& v) override { v.visit(*this); } 
      virtual int getPrice() const { return 210; }
      virtual int getStars() const { return 3; }
   };
   
   struct Hiking : API::Element, API::Fun
   {
      virtual void accept(API::Visitor& v) override { v.visit(*this); } 
      virtual int getPrice() const { return 0; }
      virtual int getRelaxFactor() const { return 5; }
   };
   
   struct Price : public API::Visitor
   {
      Price() : m_price(0) {}

      virtual void visit(API::Accomodation& a) override
      {  m_price += a.getPrice(); }

      virtual void visit(API::Traveling& t) override
      {  m_price += t.getPrice() * 2 /* there and back */; }

      virtual void visit(API::Fun& f) override
      {  m_price += f.getPrice(); }

      virtual std::string toString() const override
      {  return std::to_string(m_price); }
      
   private:
      int m_price;
   };
   
   struct Comfort : public API::Visitor
   {
      Comfort() : m_comfort(1.) {}

      virtual void visit(API::Accomodation& a) override
      {  m_comfort *= 1. + a.getStars(); }

      virtual void visit(API::Traveling& t) override
      {  m_comfort *= 1. / t.getClass(); }

      virtual void visit(API::Fun& f) override
      {  /* does nothing */ }

      virtual std::string toString() const override
      {  return std::to_string(m_comfort); }
      
   private:
      double m_comfort;
   };
   
   struct Relaxation : public API::Visitor
   {
      Relaxation() : m_relaxation(1.) {}
      
      virtual void visit(API::Accomodation& a) override
      {  m_relaxation *= 1. + a.getStars(); }

      virtual void visit(API::Traveling& t) override
      {  m_relaxation *= 1. / ((t.getDistance() / 100.) * t.getClass()); }

      virtual void visit(API::Fun& f) override
      {  m_relaxation *= f.getRelaxFactor(); }
      
      virtual std::string toString() const override
      {  return std::to_string(m_relaxation); }
      
   private:
      double m_relaxation;
   };
}
