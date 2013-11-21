// OpenSSLTest

#include "ssl_socket.h"

namespace net {

SSLSocket::SSLSocket() : Socket(), _ssl(nullptr) {}

SSLSocket::~SSLSocket() {}

bool SSLSocket::DoConnect(const std::string& connectionString) {


  return true;
}

}  // namespace net
