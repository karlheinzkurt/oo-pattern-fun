#pragma once

#include <iostream>
#include <memory>
#include <sstream>

namespace API
{
   struct TextInterface
   {
      virtual ~TextInterface() = default;
      
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
