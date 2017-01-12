
#include "Observer.h"
#include "Observable.h"

#include <memory>
#include <iostream>
#include <vector>
#include <fstream>

/** Task does not have to know about concrete type of progress bars 
 */
struct ComplexTask : Concrete::Observable<int>
{
   ComplexTask(std::vector<double> numbers) : m_numbers(numbers), m_progressFactor(100. / m_numbers.size()) {}
   
   void calculate()
   {
      for (size_t i(0); i < m_numbers.size(); ++i)
      {  
         notify(static_cast<int>(i * m_progressFactor));
         m_numbers[i] *= 2.;         
      }
   }
   
private:
   std::vector<double> m_numbers;
   double m_progressFactor;
};

struct ProgressView : API::Observer<int>
{
   ProgressView(std::ostream& os) : m_os(os) {}
   
   virtual void update(int const& progress)
   {  m_os << progress << '\n'; }
   
private:
   std::ostream& m_os;
};

int main(int argc, char** argv)
{
   /* One progress information on stdout */
   ProgressView stdoutProgressView(std::cout);
   
   /* Another progress information into file */
   std::ofstream progressFile("progress.txt");
   ProgressView fileProgressView(progressFile);
   
   ComplexTask task(std::vector<double>({1,2,3,5,7,11,13,17,1,2,3,5,7,11,13,17}));
   task.attach(&stdoutProgressView);
   task.attach(&fileProgressView);
   
   task.calculate();
}
