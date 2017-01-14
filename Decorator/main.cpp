
#include "Decorator.h"

#include <iostream>

int main( int argc, char** argv )
{
   using namespace Concrete;

   /** Original object and decorated object have the same interface,
    *  so we can re-assign the decorated object to the same pointer.
    */

   std::unique_ptr<API::TextInterface> text(new TextObject("some text"));
   std::cout << *text << '\n';
   
   text = std::make_unique<PipeDecorator>(std::make_unique<MinusDecorator>(std::make_unique<PipeDecorator>(std::move(text))));
   std::cout << *text << '\n';
   
   text->setText("blub");
   std::cout << *text << '\n';
}