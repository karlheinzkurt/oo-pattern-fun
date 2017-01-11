#pragma once

namespace API
{
   template <typename ArgumentT>
   struct Observer
   {
      virtual ~Observer() = default;

      virtual void update(ArgumentT const&) = 0;
   };

   /** void argument type needs partial specialization for update */
   template <>
   struct Observer<void>
   {
      virtual void update() = 0;
   };
}
