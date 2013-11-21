// OpenSSLTest

#ifndef SOCKET_H_
#define SOCKET_H_

#include <openssl/bio.h>
#include <string>

namespace net {

class Socket {
public:
  Socket();
  virtual ~Socket();

  bool Connect(const std::string& hostname, int port);
  void Disconnect();

  int Read(char* buffer, int bufferSize);
  int Write(const char* buffer, int bufferSize);

protected:
  virtual bool DoConnect(const std::string& connectionString);

  BIO* _bio;
};

}  // namespace net

#endif  // SOCKET_H_
