// OpenSSLTest

#include "client_socket.h"

#include <cassert>
#include <iostream>

namespace net {

ClientSocket::ClientSocket() {
}

ClientSocket::~ClientSocket() {

}

bool ClientSocket::DoConnect(const std::string& connectionString) {
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

void ClientSocket::DoDisconnect() {
  _bio.Reset(nullptr);
}

int ClientSocket::DoRead(char* buffer, int bufferSize) {
  assert(bufferSize > 0);

  int bytesRead = BIO_read(_bio.Get(), buffer, bufferSize);
  if (bytesRead == 0) {
    _connected = false;
    return bytesRead;
  } else if (bytesRead < 0) {
    if (BIO_should_retry(_bio.Get())) {
      return DoRead(buffer, bufferSize);
    }
  }

  return bytesRead;
}

int ClientSocket::DoWrite(const char* buffer, int bufferSize) {
  assert(bufferSize > 0);

  int bytesWritten = BIO_write(_bio.Get(), buffer, bufferSize);
  if (bytesWritten == 0) {
    _connected = false;
    return bytesWritten;
  } else if (bytesWritten < 0) {
    if (BIO_should_retry(_bio.Get())) {
      return DoWrite(buffer, bufferSize);
    }
  }

  return bytesWritten;
}

}  // namespace net
