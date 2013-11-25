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
  virtual bool DoConnect(const std::string& connectionString) = 0;
  virtual void DoDisconnect() = 0;

  virtual int DoRead(char* buffer, int bufferSize) = 0;
  virtual int DoWrite(const char* buffer, int bufferSize) = 0;

  // Whether the connection is active or not.
  bool _connected;
};

}  // namespace net

#endif  // SOCKET_H_
