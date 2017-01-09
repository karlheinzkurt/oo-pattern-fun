
#include "Visitor.h"

struct Holiday ///< Has nothing to do with visitor, but is using it
{
   Holiday(std::initializer_list<std::reference_wrapper<API::Element>> elements)
   {
      Concrete::Price price;
      Concrete::Comfort comfort;
      Concrete::Relaxation relaxation;

      for (auto& element : elements)
      {
         element.get().accept(price);
         element.get().accept(comfort);
         element.get().accept(relaxation);
      }
      
      std::ostringstream os;
      os << "Price: " << price << ", Comfort: " << comfort << ", Relaxation: " << relaxation;
      m_string = os.str();      
   }

   std::string toString() const
   {  return m_string; }
   
private:
   std::string m_string;
};

int main( int argc, char** argv )
{
   {
      Concrete::Flight flightTo(3), flightBack(3);
      Concrete::Hotel hotel;
      Concrete::Hiking hiking;
      std::cout << "Your holiday: " << Holiday({flightTo, flightBack, hotel, hiking}).toString() << '\n';
   }
   {
      Concrete::Cruise cruise;
      Concrete::Flight flightBack(2);
      std::cout << "Your holiday: " << Holiday({cruise, flightBack}).toString() << '\n';
   }
}