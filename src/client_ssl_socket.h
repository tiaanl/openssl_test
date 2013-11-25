// OpenSSLTest

#ifndef SSL_SOCKET_H_
#define SSL_SOCKET_H_

#include <openssl/ssl.h>
#include "scoped_openssl.h"
#include "client_socket.h"

namespace net {

class ClientSSLSocket : public ClientSocket {
public:
  ClientSSLSocket();
  virtual ~ClientSSLSocket();

protected:
  virtual bool DoConnect(const std::string& connectionString) override;
  virtual void DoDisconnect() override;

  virtual int DoRead(char* buffer, int bufferSize) override;
  virtual int DoWrite(const char* buffer, int bufferSize) override;

  ScopedOpenSSL<SSL_CTX, SSL_CTX_free> _ctx;
};

}  // namespace net

#endif  // SSL_SOCKET_H_
