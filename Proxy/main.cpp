
#include "Account.h"
#include "AccessController.h"

#include <iostream>
#include <memory>

int main( int argc, char** argv )
{
   Concrete::AccessController accessController({"Alf", "Batman", "Lassie", "Madonna"});
   for (auto user : {"God", "Batman", "Spiderman"})
   {
      std::cout << "----------------------------------------\n";
      try
      {
         std::unique_ptr<API::Account> account(std::make_unique<Concrete::AccountAuthorizationProxy>(
             accessController, user
            ,std::make_unique<Concrete::Account>()));
            
         ///< \todo Consider to add a disposition decorator for some of the guys

         account->book("Earnings",      Money(123, Currency::EUR));
         account->book("Child benefit", Money( 25, Currency::EUR));
         
         auto shoppingMoney(account->book("For apples, juice and oat milk", -Money(30)));         
         auto cinemaMoney(account->book("For the movie From Dusk Till Dawn and some popcorn", -(Money(25) + Money(15))));

         std::cout << "Bank account statement of '" << user << "'\n" << *account << std::endl;
      }
      catch (std::exception const& e)
      {  std::cerr << "Error: " << e.what() << std::endl; }
   }
}
