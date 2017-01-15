
#include "Decorator.h"

#include <iostream>

int main( int argc, char** argv )
{
   using namespace Concrete;

   /** Original object and decorated object have the same interface,
    *  so we can re-assign the decorated object to the same pointer.
    */

   std::unique_ptr<API::Text> text(new Text("some text"));
   std::cout << *text << '\n';
   
   text = std::make_unique<BoxDecorator>(std::make_unique<PipeDecorator>(std::move(text)));
   std::cout << *text << '\n';
   
   text->setText("some other\ntext");
   std::cout << *text << '\n';
   
   for (size_t c(0); c < 5; ++c) { text = std::make_unique<PipeDecorator>(std::move(text)); }
   std::cout << *text << '\n';
   
   text = std::make_unique<BoxDecorator>(std::move(text));
   text->setText("blub\nblub blub\nblub");
   std::cout << *text << '\n';
}