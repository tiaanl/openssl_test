// OpenSSLTest

#include "socket.h"

#include <cassert>
#include <iostream>
#include <sstream>

namespace net {

Socket::Socket() : _connected(false) {}

Socket::~Socket() {
  Disconnect();
}

bool Socket::Connect(const std::string& hostname, int port) {
  std::ostringstream ss;
  ss << hostname << ":" << port;
  std::string fullHostname = ss.str();

  _connected = DoConnect(ss.str());
  return _connected;
}

void Socket::Disconnect() {
  DoDisconnect();
  _connected = false;
}

int Socket::Read(char* buffer, int bufferSize) {
  return DoRead(buffer, bufferSize);
}

int Socket::Write(const char* buffer, int bufferSize) {
  return DoWrite(buffer, bufferSize);
}

}  // namespace net
