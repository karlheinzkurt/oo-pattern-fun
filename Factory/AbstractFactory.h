#pragma once

#include <memory>

namespace API
{
   struct Operation
   {
      virtual ~Operation() {}
      
      virtual int operate( int const a, int const b ) const = 0;       
   };

   struct OperationFactory
   {  
      virtual ~OperationFactory() {}
      
      virtual std::unique_ptr< Operation > create() = 0;
   }; 
}

namespace Concrete
{
   struct AddFactory : public API::OperationFactory
   {  
      virtual std::unique_ptr< API::Operation > create() override;
   };

   struct MultiplyFactory : public API::OperationFactory
   {  
      virtual std::unique_ptr< API::Operation > create() override;
   };

   struct ComplexCalculator 
   {  
      ComplexCalculator( std::unique_ptr< API::OperationFactory > factory );

      int calculate( int const a, int const b ) const;

   private:
      std::unique_ptr< API::OperationFactory > m_factory;
   };
}
