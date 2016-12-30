#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>

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

      void init()
      {
         if (!checkCallSet(State::Premature, [this]{ doInit(); }, State::Initialized))
         {  throw std::logic_error("Init has to be called first"); }
      }

      void configure(std::string argument)
      {
         if (!checkCallSet(State::Initialized, [this, argument]{ doConfigure(argument); }, State::Configured))
         {  throw std::logic_error("Configure has to be called second"); }
      }

      void process()
      {
         if (!checkCallSet(State::Configured, [this]{ doProcess(); }, State::Processing))
         {  throw std::logic_error("Process has to be called third"); }
      }

   private:
      /** Avoid duplication
      */
      template <typename FunctionT>
      bool checkCallSet(State stateToCheck, FunctionT&& function, State stateToSet)
      {
         if ( m_state != stateToCheck )
         {  return false; }
         
         function();
         
         m_state = stateToSet;
         return true;
      }
   
      virtual void doInit() = 0;
      virtual void doConfigure(std::string) = 0;
      virtual void doProcess() = 0;

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
      virtual void doInit() override
      {  std::cout << "Initializing\n"; }

      virtual void doConfigure(std::string argument) override
      {  std::cout << "Configuring: " << argument << '\n'; }

      virtual void doProcess() override
      {  std::cout << "Processing\n"; }
   };   
} 

int main( int argc, char** argv )
{
   try
   {
      auto processor(std::make_unique<Concrete::Processor>());
      processor->init();
      processor->configure("bla");
      processor->process();
   }
   catch (std::exception const& e )
   {  std::cout << "Error: " << e.what() << std::endl; }
}
