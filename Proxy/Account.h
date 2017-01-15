#pragma once

#include "Money.h"
#include "AccessController.h"

#include <boost/algorithm/string.hpp>

#include <iostream>
#include <sstream>
#include <list>
#include <stdexcept>

namespace API
{   
   struct Account
   {
      virtual ~Account() = default;
      
      virtual Money book(std::string reason, Money amount) = 0;
           
      virtual Money getBalance() const = 0;
      
      virtual std::list<std::string> getStatement() const = 0;
   };
   
   std::ostream& operator<<(std::ostream& os, Account const& account)
   {
      return os   << "Balance: " << account.getBalance() << '\n'
                  << boost::algorithm::join(account.getStatement(), "\n");
   }
}

namespace Concrete
{
   struct Account final : public API::Account
   {
      virtual Money book(std::string reason, Money amount) override
      {
         m_statement.emplace_back(createEntry(reason, amount));
         m_balance += amount;
         return -amount;
      }
      
      virtual Money getBalance() const override
      {  return m_balance; }
      
      std::list<std::string> getStatement() const override
      {  return m_statement; }
      
   private:
      static std::string createEntry(std::string reason, Money amount)
      {
         std::ostringstream os;
         os << " " << (amount.isNegative() ? '-' : '+' ) << " | " << amount << " | " << reason;
         return os.str();
      }
   
      Money m_balance;
      std::list<std::string> m_statement;
   };
   
   struct AccountAuthorizationProxy final : public API::Account
   {
      AccountAuthorizationProxy(API::AccessController& accessController, API::Token token, std::unique_ptr<API::Account> account) : 
          m_accessController(accessController)
         ,m_token(token)
         ,m_account(std::move(account)) 
      {}
      
      virtual Money book(std::string reason, Money amount) override
      {  return executeAuthorized([&]{ return m_account->book(reason, amount); }); }
           
      virtual Money getBalance() const override
      {  return executeAuthorized([&]{ return m_account->getBalance(); }); }
      
      virtual std::list<std::string> getStatement() const override
      {  return executeAuthorized([&]{ return m_account->getStatement(); }); }
      
   private:
      template <typename T>
      auto executeAuthorized(T&& function) const -> decltype(function())
      {
         m_accessController.ensureAuthorization(m_token);
         return function();
      }
   
      API::AccessController& m_accessController;
      API::Token m_token;
      std::unique_ptr<API::Account> m_account;
   };
}
