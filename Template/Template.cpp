#include <iostream>
#include <memory>
#include <stdexcept>

namespace API
{
   /** Public interface it non-virtual
    */
   struct Processor
   {
      enum class State
      {
          Premature
         ,Initialized
         ,Configured
         ,Processing
      };

      Processor() : m_state(State::Premature) {}

      virtual ~Processor() {}

      void Init()
      {
         if (!CheckCallSet(State::Premature, [this]{ DoInit(); }, State::Initialized))
         {  throw std::logic_error("Init has to be called first"); }
      }

      void Configure(std::string argument)
      {
         if (!CheckCallSet(State::Initialized, [this, argument]{ DoConfigure(argument); }, State::Configured))
         {  throw std::logic_error("Configure has to be called second"); }
      }

      void Process()
      {
         if (!CheckCallSet(State::Configured, [this]{ DoProcess(); }, State::Processing))
         {  throw std::logic_error("Process has to be called third"); }
      }

   private:
      /** Avoid duplication
      */
      template <typename FunctionT>
      bool CheckCallSet(State stateToCheck, FunctionT&& function, State stateToSet)
      {
         if ( m_state != stateToCheck )
         {  return false; }
         
         function();
         
         m_state = stateToSet;
         return true;
      }
   
      virtual void DoInit() = 0;
      virtual void DoConfigure(std::string) = 0;
      virtual void DoProcess() = 0;

   private:
      State m_state;
   };
} // API

namespace Concrete
{
   /** Customization of Init/Configure/Process is possible,
       but outer frame is fixed in base class and cannot be misused.
    */
   struct Processor : API::Processor
   {
      virtual void DoInit() override
      {  std::cout << "Initializing\n"; }

      virtual void DoConfigure(std::string argument) override
      {  std::cout << "Configuring: " << argument << '\n'; }

      virtual void DoProcess() override
      {  std::cout << "Processing\n"; }
   };   
} 

int main( int argc, char** argv )
{
   try
   {
      auto processor = std::make_unique<Concrete::Processor>();
      processor->Init();
      processor->Configure("bla");
      processor->Process();
   }
   catch (std::exception const& e )
   {  std::cout << "Error: " << e.what() << std::endl; }
}
