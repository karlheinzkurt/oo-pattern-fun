
#include "Decorator.h"

#include <iostream>

int main( int argc, char** argv )
{
   /** Original object and decorated object have the same interface,
    *  so we can re-assign the decorated object to the same pointer.
    */

   std::unique_ptr<API::Text> text(new Concrete::Text("some text"));
   std::cout << *text << '\n';
   
   text = std::make_unique<Concrete::BoxDecorator>(std::make_unique<Concrete::PipeDecorator>(std::move(text)));
   std::cout << *text << '\n';
   
   text->setText("some other\ntext");
   std::cout << *text << '\n';
   
   for (size_t c(0); c < 5; ++c) { text = std::make_unique<Concrete::PipeDecorator>(std::move(text)); }
   std::cout << *text << '\n';
   
   text = std::make_unique<Concrete::BoxDecorator>(std::move(text));
   text->setText("blub\nblub blub\nblub");
   std::cout << *text << '\n';
}