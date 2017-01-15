#pragma once

#include <map>
#include <set>
#include <string>
#include <atomic>
#include <list>

namespace Detail
{
   std::atomic< int > s_id(0);
}

namespace API
{
   struct Token
   {
      Token() : id(++Detail::s_id) {}
   
      bool operator<(Token const& other) const
      {  return id < other.id; }
      
   private:
      int id;
   };
   
   struct User
   {
      User(std::string name, int pin) : m_name(name), m_pin(pin) {}
      
      bool equals(std::string name) const
      {  return m_name.compare(name) == 0; }
      
      bool operator<(User const& other) const
      {  return std::tie(m_name, m_pin) < std::tie(other.m_name, other.m_pin); }
      
   private:
      std::string m_name;
      int m_pin;
   };
      
   struct AccessController
   {
      virtual ~AccessController() = default;
      
      virtual Token authorize(std::string user, std::istream& is) = 0;
      
      virtual void ensureAuthorization(API::Token token) const = 0;
   };
}

namespace Concrete
{
   struct AccessController : API::AccessController
   {
      AccessController(std::set<API::User> authorizedUsers) : m_users(std::move(authorizedUsers)) 
      {}
      
      virtual API::Token authorize(std::string user, std::istream& is) override
      {
         std::string pin;
         is >> pin;
         auto entry(m_users.find(API::User(user, std::stoi(pin))));
         if (entry == m_users.end())
         {  throw std::domain_error(std::string("Access denied for: ") + user); }
                  
         return *m_tokens.emplace(API::Token()).first;
      }
      
      virtual void ensureAuthorization(API::Token token) const override
      {  
         auto entry(m_tokens.find(token));
         if (entry == m_tokens.end())
         {   throw std::domain_error("Unauthorized access"); }
      }
      
   private:
      std::set<API::User> m_users;
      std::set<API::Token> m_tokens;
   };   
}
