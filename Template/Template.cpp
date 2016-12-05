#include <iostream>

namespace API
{
   class Processor
   {
      private:
      enum eSTATE
      {  eSTATE_PREMATURE = 0x1, eSTATE_INITIALIZED = 0x2, eSTATE_CONFIGURED = 0x4, eSTATE_PROCESSING = 0x8 };

      public:
      Processor() : m_State( eSTATE_PREMATURE ) {}

      virtual ~Processor() {}

      void Init()
      {
         if ( m_State != eSTATE_PREMATURE ) 
         {  throw "Double initialization"; }
         
         DoInit();

         m_State = eSTATE_INITIALIZED;
      }

      void Configure()
      {
         if ( m_State != eSTATE_INITIALIZED ) 
         {  throw "Init has to be called first"; }
         
         DoConfigure();

         m_State = eSTATE_CONFIGURED;
      }

      void Process()
      {
         if ( m_State != eSTATE_CONFIGURED )
         {  throw "Init and configure has to be called at first"; }

         m_State = eSTATE_PROCESSING;

         DoProcess();
      }

      private:
      virtual void DoInit() = 0;
      virtual void DoConfigure() = 0;
      virtual void DoProcess() = 0;

      private:
      eSTATE m_State;
   };
} // API

namespace Concrete
{
   class Processor : public API::Processor
   {
      private: 
      void DoInit()
      {  std::cout << "initializing" << std::endl; }

      void DoConfigure()
      {  std::cout << "configuring" << std::endl; }

      void DoProcess()
      {  std::cout << "processing" << std::endl; }
   };   
} // Concrete

int main( int argc, char** argv )
{
   try
   {
      API::Processor* p = new Concrete::Processor();
      p->Init();
      p->Configure();
      p->Process();
   }
   catch ( const char* c )
   {  std::cout << "Error: " << c << std::endl; }

   return 0;
}

