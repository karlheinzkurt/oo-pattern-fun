
/** We don't need to include std::string here
 *  even when we use it inside of the processor.
 */

namespace Concrete
{
   struct Processor
   {
      Processor(char const* const text);
      ~Processor();
      
      Processor(Processor const&) = delete;
      Processor& operator==(Processor const&) = delete;
      Processor(Processor&&) = delete;
      Processor& operator==(Processor&&) = delete;      
      
      void print() const;
   
   private:   
      /** See Scott Meyers Effective Modern C++ about Pimpl and:
            - copyable/movable
            - unique_ptr/shared_ptr
       */
      struct Impl;
      Impl* m_pimpl;
   };
}
