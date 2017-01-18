#pragma once

#include <sstream>
#include <iomanip>
#include <stdexcept>

enum class Currency
{
    EUR
   ,USD
};

std::ostream& operator<<(std::ostream& os, Currency c)
{
   switch(c)
   {
      case Currency::EUR: return os << "EUR";
      case Currency::USD: return os << "USD";
   }
   throw std::logic_error("Currency not supported");
}

struct Money
{
   Money() : m_amount(0), m_currency(Currency::EUR)
   {}
   
   Money(int amount, Currency currency = Currency::EUR) : m_amount(amount), m_currency(currency)
   {}
   
   Money operator-() const
   {  return Money(-m_amount, m_currency); }
        
   Money& operator+=(Money const& other)
   {  
      if (m_currency != other.m_currency) 
      {  throw std::invalid_argument("Currency not equal"); }
      
      m_amount += other.m_amount; 
      return *this;
   }
   
   bool isNegative() const
   {  return m_amount < 0; }
   
   std::string toString() const
   {
      std::ostringstream os;
      os << std::setw(3) << m_amount << " " << m_currency;
      return os.str();
   }
   
private:
   int m_amount;
   Currency m_currency;
};

Money operator+(Money const& a, Money const& b)
{  return (Money() += a) += b; }

std::ostream& operator<<(std::ostream& os, Money const& money)
{  return os << money.toString(); }
