#include <iostream>

namespace API
{
   class Strategy
   {
      public:
      virtual ~Strategy() {}
      virtual void Do() = 0;
   };

   template < class CONCRETE_STRATEGY >
   class WithStrategy
   {
      public: 
      WithStrategy( Strategy* strategy ) : m_strategy( strategy ) {}
      ~WithStrategy() { delete m_strategy; }

      protected:
      void Do() { m_strategy->Do(); }

      private:
      Strategy* m_strategy;
   };
}

namespace Concrete
{
   class FlyingStrategy : public API::Strategy
   { public: void fly() { Do(); }; };

   class ShowingStrategy : public API::Strategy
   { public: void show() { Do(); }; };

   class NonFlyingStrategy : public FlyingStrategy
   {  void Do() { std::cout << "non flying" << std::endl; } };

   class NormalFlyingStrategy : public FlyingStrategy
   {  void Do() { std::cout << "normal flying" << std::endl; } };

   class ComicShowingStrategy : public ShowingStrategy
   {  void Do() { std::cout << "artificial showing" << std::endl; } };

   class RealisticShowingStrategy : public ShowingStrategy
   {  void Do() { std::cout << "show image" << std::endl; } };

   class Duck : 
      public API::WithStrategy< FlyingStrategy >, 
      public API::WithStrategy< ShowingStrategy >
   {
      public: 
      Duck( API::Strategy* flyingStrategy, API::Strategy* showingStrategy ) : 
          API::WithStrategy< FlyingStrategy >( flyingStrategy ) 
         ,API::WithStrategy< ShowingStrategy >( showingStrategy )
      {}
      void fly()  { WithStrategy< FlyingStrategy >::Do(); } 
      void show() { WithStrategy< ShowingStrategy >::Do(); }
   };

   class RubberDuck : public Duck
   { public: RubberDuck() : Duck( new NonFlyingStrategy, new ComicShowingStrategy ) {} };
   
   class MallardDuck : public Duck
   { public: MallardDuck() : Duck( new NormalFlyingStrategy, new RealisticShowingStrategy ) {} };
}
   
int main ( int, char** )
{
   Concrete::Duck* ducks[2] = { new Concrete::RubberDuck, new Concrete::MallardDuck };
   ducks[0]->fly(), ducks[0]->show();
   ducks[1]->fly(), ducks[1]->show();
   delete ducks[0], delete ducks[1];
   return 0;
}

