// OpenSSLTest

#ifndef SSL_SOCKET_H_
#define SSL_SOCKET_H_

#include "scoped_openssl.h"
#include "socket.h"
#include <openssl/ssl.h>

namespace net {

class SSLSocket : public Socket {
public:
  SSLSocket();
  virtual ~SSLSocket();

protected:
  virtual bool DoConnect(const std::string& connectionString);
  virtual void DoDisconnect();

  ScopedOpenSSL<SSL_CTX, SSL_CTX_free> _ctx;
};

}  // namespace net

#endif  // SSL_SOCKET_H_
