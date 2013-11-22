// OpenSSLTest

#ifndef SOCKET_H_
#define SOCKET_H_

#include <openssl/bio.h>
#include <string>
#include "scoped_openssl.h"

namespace net {

class Socket {
public:
  Socket();
  virtual ~Socket();

  bool IsConnected() const { return _connected; }

  bool Connect(const std::string& hostname, int port);
  void Disconnect();

  int Read(char* buffer, int bufferSize);
  int Write(const char* buffer, int bufferSize);

protected:
  virtual bool DoConnect(const std::string& connectionString);
  virtual void DoDisconnect();

  // Whether the connection is active or not.
  bool _connected;

  ScopedOpenSSL<BIO, BIO_free_all> _bio;
};

}  // namespace net

#endif  // SOCKET_H_
