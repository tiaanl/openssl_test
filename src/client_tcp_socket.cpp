// OpenSSLTest

#include "client_tcp_socket.h"

#include <cassert>
#include <iostream>

namespace net {

ClientTCPSocket::ClientTCPSocket() {}

ClientTCPSocket::~ClientTCPSocket() {
  Disconnect();
}

bool ClientTCPSocket::Connect(std::string hostAndPort) {
  _bio.Reset(BIO_new_connect(const_cast<char*>(hostAndPort.c_str())));
  if (!_bio.Get()) {
    std::cerr << "ERROR: Could not create connection." << std::endl;
    return false;
  }

  long connectResult = BIO_do_connect(_bio.Get());
  if (connectResult <= 0) {
    std::cerr << "ERROR: Could not connect to \"" << hostAndPort << "\"."
              << std::endl;
    return false;
  }

  return true;
}

void ClientTCPSocket::Disconnect() { _bio.Reset(nullptr); }

bool ClientTCPSocket::Read(char* buffer, int bufferSize, int* bytesRead) {
  assert(buffer);
  assert(bufferSize > 0);

  int rv = BIO_read(_bio.Get(), buffer, bufferSize);

  if (bytesRead)
    *bytesRead = (rv <= 0) ? 0 : rv;

  if (rv <= 0) {
    if (rv == 0 && BIO_should_retry(_bio.Get()))
      return Read(buffer, bufferSize, bytesRead);
    return false;
  }

  return true;
}

bool ClientTCPSocket::Write(const char* buffer, int bufferSize,
                            int* bytesWritten) {
  assert(buffer);
  assert(bufferSize > 0);

  int rv = BIO_write(_bio.Get(), buffer, bufferSize);

  if (bytesWritten)
    *bytesWritten = (rv <= 0) ? 0 : rv;

  if (rv <= 0) {
    if (rv == 0 && BIO_should_retry(_bio.Get()))
      return Write(buffer, bufferSize, bytesWritten);
    return false;
  }

  return true;
}

}  // namespace net
