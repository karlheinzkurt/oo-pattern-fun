
#include "Composite.h"

#include <iostream>

std::unique_ptr<API::Graphic> createComplexGraphics()
{
   auto container(std::make_unique<Concrete::GraphicComposite>());
   container->add(std::make_unique<Concrete::Circle>());
   {
      Concrete::GraphicComposite& subContainer(container->addSubGraphic());
      subContainer.add(std::make_unique<Concrete::Rectangle>());
      {
         Concrete::GraphicComposite& subSubContainer(subContainer.addSubGraphic());
         subSubContainer.add(std::make_unique<Concrete::Circle>());
      }
      subContainer.add(std::make_unique<Concrete::Circle>());
   }
   container->add(std::make_unique<Concrete::Rectangle>());
   return container;
}

int main( int argc, char** argv )
{
   /** Both have the same interface but the first
       contains sub graphic elements.
    */
   std::unique_ptr<API::Graphic> graphicsA(createComplexGraphics());
   std::unique_ptr<API::Graphic> graphicsB(std::make_unique<Concrete::Rectangle>());
   
   std::cout << *graphicsA << '\n'
             << *graphicsB << '\n';
}