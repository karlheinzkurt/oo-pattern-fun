#include <iostream>
#include <memory>
#include <array>

namespace API
{
   struct Flyable
   {
      virtual ~Flyable() = default;
      
      virtual void fly() = 0;
   };
   
   struct Drawable
   {
      virtual ~Drawable() = default;

      virtual void draw() = 0;
   };
   
   struct Duck : public API::Flyable, public API::Drawable {};
}

namespace Detail
{
   struct DuckBase : public API::Duck ///< Helper to avoid duplications
   {
   protected:
      DuckBase(std::unique_ptr<API::Flyable> flyingStrategy, std::unique_ptr<API::Drawable> drawingStrategy) : 
          m_flyingStrategy(std::move(flyingStrategy)) 
         ,m_drawingStrategy(std::move(drawingStrategy))
      {}
      
   public:
      virtual void fly() override { m_flyingStrategy->fly(); } 
      virtual void draw() override { m_drawingStrategy->draw(); }
      
   private:
      std::unique_ptr<API::Flyable> m_flyingStrategy;
      std::unique_ptr<API::Drawable> m_drawingStrategy;
   };
   
   class NonFlyingStrategy : public API::Flyable
   {  
      virtual void fly() override { std::cout << "cannot fly" << std::endl; }
   };

   class NormalFlyingStrategy : public API::Flyable
   {  
      virtual void fly() override { std::cout << "just fly" << std::endl; } 
   };

   class ComicDrawingStrategy : public API::Drawable
   {  
      virtual void draw() override { std::cout << "draw comic like" << std::endl; } 
   };

   class RealisticDrawingStrategy : public API::Drawable
   {  
      virtual void draw() override { std::cout << "draw picture" << std::endl; } 
   };  
}

namespace Concrete
{
   struct MallardDuck : public Detail::DuckBase ///< Can fly and looks realistic
   {  
      MallardDuck() : Detail::DuckBase(
          std::make_unique<Detail::NormalFlyingStrategy>()
         ,std::make_unique<Detail::RealisticDrawingStrategy>()) 
      {}
   };
   
   struct PekinDuck : public Detail::DuckBase ///< Cannot fly and looks realistic
   {  
      PekinDuck() : Detail::DuckBase(
          std::make_unique<Detail::NonFlyingStrategy>()
         ,std::make_unique<Detail::RealisticDrawingStrategy>()) 
      {}
   };
   
   struct RubberDuck : public Detail::DuckBase ///< Cannot fly and does not look realistic
   {  
      RubberDuck() : Detail::DuckBase(
          std::make_unique<Detail::NonFlyingStrategy>()
         ,std::make_unique<Detail::ComicDrawingStrategy>()) 
      {}
   };
}
   
int main ( int, char** )
{
   std::array<std::unique_ptr<API::Duck>, 3> duckGame = 
   { 
       std::make_unique<Concrete::RubberDuck>()
      ,std::make_unique<Concrete::MallardDuck>() 
      ,std::make_unique<Concrete::PekinDuck>() 
   };
   
   for (auto& duck : duckGame) ///< Think as we would play the duck game
   {
      duck->fly();
      duck->draw();
   }
}
