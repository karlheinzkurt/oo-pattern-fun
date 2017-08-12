
#include "Interpreter.h"

#include <iostream>
#include <sstream>

int main( int argc, char** argv )
{      
   try
   {
      std::stringstream s(
      "@~~~~~~~~~~@~~~~~~~~~~~~~~~~~~~~~@~~~~~~~~~~~@\n"
      "@ Key1     @ Description1        @ 3         @     \n"
      "@Key2      @ Description2        @ Value2    @\n"
      "@~~~~~~~~~~@~~~~~~~~~~~~~~~~~~~~~@~~~~~~~~~~~@\n"
      "@~~~~~~~~~~@~~~~~~~~~~~~~~~~~~~~~@~~~~~~~~~~~@\n"
      "@ Key3     @ Description3        @Value3 aaaahh... sorry@\n"
      "@ E-Mail   @ E-Mail description  @one\\@two.de@\n"
      "@ Key4     @ Multi               @ Value4    @\n"
      "  @        @  line line line line@           @\n"
      "@          @ description         @           @ \n"
      "@Key5Key5Key5@ Description5      @ Value5    @\n"
      "@  Longer Key@ Description6      @     Value6@\n"
      "@~~~~~~~~~~@~~~~~~~~~~~~~~~~~~~~~@~~~~~~~~~~~@\n"
      );

      Concrete::Context context(s, Detail::ColumnSeparator('@'), Detail::SectionSeparator('~'));
      API::EntryMapType const entryMap(Concrete::StreamInterpreter().evaluate(context).getEntryMap());
      
      std::cout << "Value of 'Key1': " << entryMap.at("Key1").m_value << '\n';
      
      std::cout << "Description of 'Key4': " << entryMap.at("Key4").m_description << '\n';
      
      std::cout << "Entry for 'Longer Key': " << entryMap.at("Longer Key") << '\n';
      
      std::cout << "Entry for 'E-Mail': " << entryMap.at("E-Mail") << '\n';

      std::cout << "\n\n" << entryMap;
   }
   catch (std::exception const& e)
   {  std::cerr << "Error: " << e.what() << std::endl; }
}
