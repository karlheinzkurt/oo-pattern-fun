#pragma once

#include "Observer.h"

#include <list>

namespace API
{
	template <typename ArgumentT>
	struct Observable
	{
      virtual ~Observable() = default;

		virtual void attach(Observer<ArgumentT>* const) = 0;

		virtual void detach(Observer<ArgumentT>* const) = 0;
      
      virtual void notify(ArgumentT const&) = 0;
	};
   
   /** void argument type needs partial specialization for notify */
   template <>
	struct Observable<void>
	{      
      virtual void notify() = 0;
	};
}

namespace Concrete
{
	template <typename ArgumentT>
	struct Observable : API::Observable<ArgumentT>
	{
		virtual void attach(API::Observer<ArgumentT>* const observer) override
      {  m_observers.push_back(observer); }

		virtual void detach(API::Observer<ArgumentT>* const observer) override
      {  m_observers.remove(observer); }

      virtual void notify(ArgumentT const& argument) override
      {
         for (auto const o : this->m_observers)
         {  o->update(argument); }
      }

   protected:
		std::list<API::Observer<ArgumentT>*> m_observers;
	};

   /** void argument type needs partial specialization for notify */
	template <>
	struct Observable<void> : API::Observable<void>
	{
		virtual void notify() override
      {
         for (auto const o : this->m_observers)
         {  o->update(); }
      }
      
   protected:
		std::list<API::Observer<void>*> m_observers;
	};
}
