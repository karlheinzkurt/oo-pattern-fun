
#include "Chain.h"

#include <iostream>
#include <memory>

struct ATM : API::Handler
{
   ATM()
   {
      /** Priority: Our ATM should give at least 3 10 euro notes when possible,
                    but maybe even more
       */
      auto root(std::make_unique<Concrete::NoteHandler>( 10, 3));
      root->add(std::make_unique<Concrete::NoteHandler>(100));
      root->add(std::make_unique<Concrete::NoteHandler>( 50));
      root->add(std::make_unique<Concrete::NoteHandler>( 20));
      root->add(std::make_unique<Concrete::NoteHandler>( 10));
      root->add(std::make_unique<Concrete::NoteHandler>(  5));
      root->add(std::make_unique<Concrete::CoinHandler>(  2));
      root->add(std::make_unique<Concrete::CoinHandler>(  1));
      m_root = std::move(root);
   }
   
   virtual void handle(std::unique_ptr<API::Order> order) override
   {
      m_root->handle(std::move(order));
   }
   
private:
   std::unique_ptr<API::Handler> m_root;
};

int main(int argc, char** argv)
{
   ATM atm;   
   atm.handle(std::make_unique<API::Order>(364));
}
