// OpenSSLTest

#include "socket.h"
#include <openssl/ssl.h>

namespace net {

class SSLSocket : public Socket {
public:
  SSLSocket();
  virtual ~SSLSocket();

protected:
  virtual bool DoConnect(const std::string& connectionString);

  SSL* _ssl;
};

}  // namespace net
