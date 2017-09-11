
#include <iostream>
#include <string>
#include <sstream>
#include <functional>

struct Error
{
   struct Build
   {
      Build() : m_type(0), m_returnValue(0), m_functionName(), m_lineNumber(0), m_progressHandler([] {}) {}
      
      Build& withType(int errorType) 
      { 
         m_type = errorType; 
         return *this; 
      }
      Build& withReturnValue(int returnValue) 
      { 
         m_returnValue = returnValue; 
         return *this; 
      }
      Build& onLocation(std::string functionName, int lineNumber) 
      { 
         m_functionName = functionName;
         m_lineNumber = lineNumber; 
         return *this; 
      }
      Build& stopExecution() 
      { 
         m_progressHandler = [] { std::terminate(); }; 
         return *this; 
      }
      Error done()
      {
         if (m_type > 23) { m_type = 0; } ///< When type is behind some limit, we reset it to unknown

         /** We can/should do further checks here
         */

         std::ostringstream os;
         os << "type: " << m_type << ", "
            << "return value: " << m_returnValue << ", "
            << "location: " << m_functionName << " (" << m_lineNumber << ")";

         return Error(os.str(), m_progressHandler);
      }
           
   private:
      int m_type;
      int m_returnValue;
      std::string m_functionName;
      int m_lineNumber;
      std::function<void()> m_progressHandler;
   };
         
   std::string toString() const
   { 
      std::ostringstream os;
      os << "Error occurred: " << m_message;
      return os.str();
   }
   void handleProgress() const 
   { 
      m_progressHandler(); 
   }
   
private:
   /** Private ctor, use the builder to create an instance of Error
   */
   Error(std::string message, std::function<void()> progressHandler) : m_message(message), m_progressHandler(progressHandler) {}

   std::string m_message;
   std::function<void()> m_progressHandler;
};

std::ostream& operator<<(std::ostream& os, Error const& e) { return os << e.toString(); }

void handle(Error e) 
{ 
   std::cerr << e << '\n';
   e.handleProgress(); 
}
