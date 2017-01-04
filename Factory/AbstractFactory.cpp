#include "AbstractFactory.h"

namespace Concrete
{
   struct Add : public API::Operation ///< Concrete operation could be hidden
   {  
      virtual int operate( int const a, int const b ) const override
      {  return ( a + b ); }
   };

   struct Multiply : public API::Operation ///< Concrete operation could be hidden
   {
      virtual int operate( int const a, int const b ) const override
      {  return ( a * b ); }
   };

   std::unique_ptr< API::Operation > AddFactory::create()
   {  return std::make_unique< Add >(); }

   std::unique_ptr< API::Operation > MultiplyFactory::create()
   {  return std::make_unique< Multiply >(); }

   ComplexCalculator::ComplexCalculator( std::unique_ptr< API::OperationFactory > factory ) : m_factory( std::move( factory ) ) 
   {}

   int ComplexCalculator::calculate( int const a, int const b ) const
   {  
      auto operation = m_factory->create();
      return operation->operate( a, b );
   }
}
