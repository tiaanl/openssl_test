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
  assert(bufferSize > 0);

  int bytesRead = BIO_read(_bio.Get(), buffer, bufferSize);
  if (bytesRead == 0) {
    _connected = false;
    return bytesRead;
  } else if (bytesRead < 0) {
    if (BIO_should_retry(_bio.Get())) {
      return Read(buffer, bufferSize);
    }
  }

  return bytesRead;
}

int Socket::Write(const char* buffer, int bufferSize) {
  assert(bufferSize > 0);

  int bytesWritten = BIO_write(_bio.Get(), buffer, bufferSize);
  if (bytesWritten == 0) {
    _connected = false;
    return bytesWritten;
  } else if (bytesWritten < 0) {
    if (BIO_should_retry(_bio.Get())) {
      return Write(buffer, bufferSize);
    }
  }

  return bytesWritten;
}

bool Socket::DoConnect(const std::string& connectionString) {
  _bio.Reset(BIO_new_connect(const_cast<char*>(connectionString.c_str())));
  if (!_bio.Get()) {
    std::cerr << "ERROR: Could not create connection." << std::endl;
    return false;
  }

  long connectResult = BIO_do_connect(_bio.Get());
  if (connectResult <= 0) {
    std::cerr << "ERROR: Could not connect to \"" << connectionString << "\"."
              << std::endl;
    return false;
  }

  return true;
}

void Socket::DoDisconnect() {
  _bio.Reset(nullptr);
}

}  // namespace net
