// OpenSSLTest

#ifndef CLIENT_SOCKET_H_
#define CLIENT_SOCKET_H_

#include <openssl/bio.h>
#include "scoped_openssl.h"
#include "socket.h"

namespace net {

class ClientSocket : public Socket {
public:
  virtual ~ClientSocket() {}

  virtual bool Connect(std::string hostAndPort) = 0;
  virtual void Disconnect() = 0;
};

}  // namespace net

#endif  // CLIENT_SOCKET_H_
