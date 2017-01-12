#pragma once

#include <iostream>
#include <memory>
#include <limits>
#include <algorithm>

namespace API
{
   struct Order
   {
      Order(int amount) : m_amount(amount) {}
      
      int m_amount;
   };
   
   std::ostream& operator<<(std::ostream& os, Order const& order)
   {  return os << order.m_amount; }
   
   struct Handler
   {
      virtual ~Handler() = default;
      
      /** When the interface is extracted explicitly, 
          it's the command pattern quite obviously.
       */
      virtual void handle(std::unique_ptr<Order> order) = 0;
   };
}

namespace Detail
{
   struct HandlerBase : API::Handler
   {
      HandlerBase& add(std::unique_ptr<HandlerBase> next)
      {
         return (m_next ? m_next->add(std::move(next)) : *(m_next = std::move(next)));
      }

      /** Default implementation forwards always to the next.
       */
      virtual void handle(std::unique_ptr<API::Order> order) override
      {
         if (order->m_amount == 0) ///< When the requested amount of money is split, we terminate
         {  return; }
         
         if (m_next)
         {  m_next->handle(std::move(order)); }
      }

   private:
      std::unique_ptr<HandlerBase> m_next;
   };
}

namespace Concrete
{   
   struct NoteHandler : public Detail::HandlerBase
   {
      /** \param amount of the note
       *  \param count of notes requested when possible
       */
      NoteHandler(int amount, int count = std::numeric_limits<int>::max()) : m_amount(amount), m_count(count) {}
      
      virtual void handle(std::unique_ptr<API::Order> order) override
      {       
         int const count(std::min(order->m_amount / m_amount, m_count));
         order->m_amount -= m_amount * count;
         
         std::cout << "Print " << count << " notes of amount " << m_amount << '\n';

         HandlerBase::handle(std::move(order));
      }
      
   private:
      int m_amount;
      int m_count;
   };
   
   struct CoinHandler : public Detail::HandlerBase
   {
      /** \param amount of the coin
       */
      CoinHandler(int amount) : m_amount(amount) {}
      
      virtual void handle(std::unique_ptr<API::Order> order) override
      {
         int const count(order->m_amount / m_amount);
         order->m_amount -= m_amount * count;
         
         std::cout << "Produce " << count << " coins of amount " << m_amount << '\n';

         HandlerBase::handle(std::move(order));
      }
      
   private:
      int m_amount;
   };
}
