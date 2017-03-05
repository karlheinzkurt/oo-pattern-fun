
#include "Interpreter.h"

#include <iostream>
#include <sstream>

int main( int argc, char** argv )
{      
   try
   {
      std::stringstream s;
      s  << "@~~~~~~~~~~@~~~~~~~~~~~~~~~~~~~~~@~~~~~~~~~~~@\n"
         << "@ Key1     @ Description1        @ 3         @     \n"
         << "@Key2      @ Description2        @ Value2    @\n"
         << "@~~~~~~~~~~@~~~~~~~~~~~~~~~~~~~~~@~~~~~~~~~~~@\n"
         << "@~~~~~~~~~~@~~~~~~~~~~~~~~~~~~~~~@~~~~~~~~~~~@\n"
         << "@ Key3     @ Description3        @Value3 aaaahh... sorry@\n"
         << "@ Key4     @ Multi               @ Value4    @\n"
         << "@          @  line line line line@           @\n"
         << "@          @ description         @           @\n"
         << "@Key5Key5Key5@ Description5      @ Value5    @\n"
         << "@  Longer Key@ Description6      @     Value6@\n"
         << "@ E-Mail   @ E-Mail description  @one\\@two.de@\n"
         << "@~~~~~~~~~~@~~~~~~~~~~~~~~~~~~~~~@~~~~~~~~~~~@\n";

      API::Context context(s, API::ColumnSeparator('@'));
      API::EntryMapType const entryMap(Concrete::StreamInterpreter().evaluate(context).getEntryMap());
      
      std::cout << "Key1: " << entryMap.at("Key1").m_value << '\n';
      
      std::cout << "Key4: " << entryMap.at("Key4").m_description << '\n';
      
      std::cout << "Longer Key: " << entryMap.at("Longer Key") << '\n';
      
      std::cout << "E-Mail: " << entryMap.at("E-Mail") << '\n';
      
      std::cout << entryMap;
   }
   catch (std::exception const& e)
   {  std::cerr << "Error: " << e.what() << std::endl; }
}
