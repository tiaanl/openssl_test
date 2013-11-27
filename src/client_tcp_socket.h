// OpenSSLTest

#ifndef CLIENT_TCP_SOCKET_H_
#define CLIENT_TCP_SOCKET_H_

#include "client_socket.h"
#include "scoped_openssl.h"

namespace net {

class ClientTCPSocket : public ClientSocket {
public:
  ClientTCPSocket();
  virtual ~ClientTCPSocket();

  // Override ClientSocket
  virtual bool Connect(std::string hostAndPort) override;
  virtual void Disconnect() override;
  virtual bool Read(char* buffer, int bufferSize, int* bytesRead) override;
  virtual bool Write(const char* buffer, int bufferSize,
                     int* bytesWritten) override;

private:
  ScopedOpenSSL<BIO, BIO_free_all> _bio;
};

}  // namespace net

#endif  // CLIENT_TCP_SOCKET_H_
