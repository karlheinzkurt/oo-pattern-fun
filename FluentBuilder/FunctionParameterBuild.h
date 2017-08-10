
#include <iostream>
#include <string>

struct Error
{
   struct Config
   {
      Config() : m_type(0), m_returnValue(0), m_functionName(), m_lineNumber(0) {}
      
      Config& withType(int errorType) { m_type = errorType; return *this; }
      Config& withReturnValue(int returnValue) { m_returnValue = returnValue; return *this; }
      Config& onLocation(std::string functionName, int lineNumber) 
      { 
         m_functionName = functionName;
         m_lineNumber = lineNumber; 
         return *this; 
      }
      
      Error done()
      {
         if (m_type > 23) { m_type = 0; } // unknown type
         return Error(*this);
      }

      friend std::ostream& operator<<(std::ostream& os, Config const& c)
      {  return os << "with type " << c.m_type << " and return value " << c.m_returnValue << " on location " << c.m_functionName << " (" << c.m_lineNumber << ")"; }
      
   private:
      int m_type;
      int m_returnValue;
      std::string m_functionName;
      int m_lineNumber;
   };
   
   Error(Config const& c) : m_config(c) {}
   
   friend std::ostream& operator<<(std::ostream& os, Error const& e)
   {  return os << "Error " << e.m_config << " occured"; }
   
private:
   Config m_config;
};

void print(Error e) { std::cerr << e << '\n'; }