
// we don't need to include std::string here.

namespace API
{
   struct Processor
   {
      Processor();
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
