#if !defined(TRANSPORT_HXX)
#define TRANSPORT_HXX

#include <string>
#include <exception>
#include <netinet/in.h>

#include <sip2/sipstack/Fifo.hxx>

namespace Vocal2
{

class Message 
{
};


class Transport
{
   public:
      struct SendData
      {
            sockaddr_in& destination;
            //TransactionId tid;
            const char* buffer;
            size_t length;
      };

      class TransportException : public std::exception
      {
         public:
            TransportException(const std::string& msg, const std::string& file, const int line);
            virtual const char* what() const throw();
      };

      Transport(in_port_t portNum, Fifo<Message>& rxFifo);
      // !ah! need to think about type for
      // interface specification here.
      
      virtual ~Transport();
      
      virtual void send( const sockaddr_in& address, const  char* buffer, size_t length)=0; //, TransactionId txId) = 0;

      virtual void process() = 0 ;

      void run();               // will not return.
      
      void shutdown();

   protected:
      int mFd;
      in_port_t mPort;
      Fifo<SendData> mTxFifo; // owned by the transport
      Fifo<Message>& mRxFifo; // passed in

   private:

      bool mShutdown ;
};

}
#endif
