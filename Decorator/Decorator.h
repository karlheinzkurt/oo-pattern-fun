#pragma once

#include <iostream>
#include <memory>
#include <sstream>
#include <list>
#include <algorithm>

namespace API
{
   struct Text
   {
      virtual ~Text() = default;
      
      virtual void setText(std::string text) = 0;

      virtual std::string toString() const = 0;
   };
   
   std::ostream& operator<<( std::ostream& os, Text const& text )
   {  return os << text.toString(); }
}

namespace Detail
{
   typedef std::list<std::string> LineListType;
   
   LineListType SplitLines(std::string text)
   {
      std::istringstream s(text);
      std::string item;
      LineListType lines;
      while (std::getline(s, item, '\n')) { lines.push_back(item); }
      return std::move(lines);
   }
   
   size_t GetMaximumLength(LineListType const& lines)
   {
      auto const element(std::max_element(lines.begin(), lines.end(), [](auto const& a, auto const& b){ return a.size() < b.size(); }));
      return (element == lines.end() ? 0 : element->size());
   }
}

namespace Concrete
{
   struct Text final : public API::Text
   {
      Text( std::string const& text ) : m_text( text ) {}

      virtual void setText(std::string text) override
      {  m_text = text; }

      virtual std::string toString() const override
      {  return m_text; }

   private:
      std::string m_text;
   };

   struct PipeDecorator final : public API::Text
   {
      PipeDecorator( std::unique_ptr<API::Text> decoratee ) : m_decoratee(std::move(decoratee)) {} 

      virtual void setText(std::string text) override
      {  m_decoratee->setText(text); }

      virtual std::string toString() const override
      {  
         auto lines(Detail::SplitLines(m_decoratee->toString()));
         auto const length(Detail::GetMaximumLength(lines));
         
         std::ostringstream os;
         for (auto const& l : lines) { os << '|' << l << std::string(length - l.size(), ' ') << "|\n"; }
         return os.str();
      }
      
   private:
      std::unique_ptr<API::Text> m_decoratee;
   };
   
   struct BoxDecorator final : public API::Text
   {
      BoxDecorator(std::unique_ptr<API::Text> decoratee) : m_decoratee(std::move(decoratee)) {} 

      virtual void setText(std::string text) override
      {  m_decoratee->setText(text); }

      virtual std::string toString() const override
      {  
         auto lines(Detail::SplitLines(m_decoratee->toString()));
         auto const length(Detail::GetMaximumLength(lines));
         lines.emplace_front(std::string(length, '-'));
         lines.emplace_back(lines.front());
         
         std::ostringstream os;
         for (auto const& l : lines) { os << '|' << l << std::string(length - l.size(), ' ') << "|\n"; }
         return os.str();
      }
     
   private:   
      std::unique_ptr<API::Text> m_decoratee;
   };
} // Concrete
