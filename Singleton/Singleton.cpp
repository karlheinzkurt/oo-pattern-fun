
#include <iostream>

class Server
{
   public:
      template< typename T = Server > static Server* Instance( ) 
      {  return ( s_instance ? s_instance : ( s_instance = new T( ) ) );}
   
      virtual void Do() 
      {  std::cout << "Server" << std::endl; }

      virtual ~Server() {}

   protected:
      Server() : m_context( 0 ) {};

   private:
      Server( Server const& );
      Server& operator=( Server const & );

      int m_context;

   private:
      static Server* s_instance;
};

Server* Server::s_instance = NULL;

class SuperServer : public Server
{
   public:
      void Do()
      {  std::cout << "Super server" << std::endl; }   

   protected:
      SuperServer() {}   
};

int main( int argc, char** argv )
{
   Server* s = Server::Instance();
   s->Do();
}
