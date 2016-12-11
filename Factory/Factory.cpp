#include <iostream>
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
   struct Add : public API::Operation
   {  
      virtual int operate( int const a, int const b ) const override
      {  return ( a + b ); }
   };

   struct Multiply : public API::Operation
   {
      virtual int operate( int const a, int const b ) const override
      {  return ( a * b ); }
   };

   struct AddFactory : public API::OperationFactory
   {  
      virtual std::unique_ptr< API::Operation > create() override
      {  return std::make_unique< Add >(); }
   };

   struct MultiplyFactory : public API::OperationFactory
   {  
      virtual std::unique_ptr< API::Operation > create() override
      {  return std::make_unique< Multiply >(); }
   };

   struct ComplexCalculator 
   {  
      ComplexCalculator( std::unique_ptr< API::OperationFactory > factory ) : m_factory( std::move( factory ) ) {}

      int calculate( size_t const count, int const a, int const b ) const
      {  
         std::unique_ptr< API::Operation > operation = m_factory->create();
         int result( 0 );
         for ( size_t c( 0 ); c < count; ++c )
         {  result += operation->operate( a, b ); }
         return result;
      }      

   private:
      std::unique_ptr< API::OperationFactory > m_factory;
   };
}

int main( int argc, char** argv )
{
   {
      Concrete::ComplexCalculator calculator( std::make_unique< Concrete::MultiplyFactory >() );
      std::cout << calculator.calculate( 10, 5, 23 ) << "\n";
   }
   {
      Concrete::ComplexCalculator calculator( std::make_unique< Concrete::AddFactory >() );
      std::cout << calculator.calculate( 10, 5, 23 ) << "\n";
   }
}
