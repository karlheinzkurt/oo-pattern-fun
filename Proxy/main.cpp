
#include "Account.h"
#include "AccessController.h"

#include <iostream>
#include <memory>

int main( int argc, char** argv )
{
   Concrete::AccessController accessController({
       API::User("Alf", 1234), API::User("Batman", 23)
      ,API::User("Lassie", 5) ,API::User("Madonna", 3)});
      
   try
   {
      std::stringstream s;
      s << 23; ///< Fill stream that we can fake we are reading pin from stdin
      
      std::unique_ptr<API::Account> account(std::make_unique<Concrete::AccountAuthorizationProxy>(
          accessController, accessController.authorize("Batman", s)
         ,std::make_unique<Concrete::Account>()));
         
      account->book("Earnings",      Money(123, Currency::EUR));
      account->book("Child benefit", Money( 25, Currency::EUR));
      
      auto shoppingMoney(account->book("For apples, juice and oat milk", -Money(30)));         
      auto cinemaMoney(account->book("For the movie From Dusk Till Dawn and some popcorn", -(Money(25) + Money(15))));

      std::cout << std::string(80, '-') << '\n'
                << "Bank account statement\n" << *account << '\n'
                << std::string(80, '-') << '\n';
   }
   catch (std::exception const& e)
   {  std::cerr << "Error: " << e.what() << std::endl; }

   try
   {
      std::unique_ptr<API::Account> account(std::make_unique<Concrete::AccountAuthorizationProxy>(
          accessController, API::Token()
         ,std::make_unique<Concrete::Account>()));
         
      account->book("Earnings", Money(123, Currency::EUR)); ///< Should throw unauthorized
   }
   catch (std::exception const& e)
   {  std::cerr << "Error: " << e.what() << std::endl; }
}
