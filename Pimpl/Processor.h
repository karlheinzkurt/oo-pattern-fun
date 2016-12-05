
// we don't need to include std::string here.

namespace API
{
   class Processor
   {
      public:
      Processor();
      ~Processor();
      void Print( void ) const;
   
      private:
      class PrivateProcessor;
      PrivateProcessor* m_p;            
   };
}
