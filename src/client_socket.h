// OpenSSLTest

#ifndef CLIENT_SOCKET_H_
#define CLIENT_SOCKET_H_

#include <openssl/bio.h>
#include "scoped_openssl.h"
#include "socket.h"

namespace net {

class ClientSocket : public Socket {
public:
  ClientSocket();
  virtual ~ClientSocket();

protected:
  virtual bool DoConnect(const std::string& connectionString) override;
  virtual void DoDisconnect() override;

  virtual int DoRead(char* buffer, int bufferSize) override;
  virtual int DoWrite(const char* buffer, int bufferSize) override;

  ScopedOpenSSL<BIO, BIO_free_all> _bio;
};

}  // namespace net

#endif  // CLIENT_SOCKET_H_
