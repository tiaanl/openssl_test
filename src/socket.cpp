// OpenSSLTest

#include "socket.h"

#include <iostream>
#include <sstream>

namespace net {

Socket::Socket() : _bio(nullptr) {}

Socket::~Socket() {
  Disconnect();
}

bool Socket::Connect(const std::string& hostname, int port) {
  std::ostringstream ss;
  ss << hostname << ":" << port;
  std::string fullHostname = ss.str();

  return DoConnect(ss.str());
}

void Socket::Disconnect() {
  if (_bio) {
    BIO_reset(_bio);
    BIO_free_all(_bio);
  }
  _bio = nullptr;
}

int Socket::Read(char* buffer, int bufferSize) {
  int bytesRead = BIO_read(_bio, buffer, bufferSize);
  if (bytesRead == 0) {
    // Handle closed connection.
  } else if (bytesRead < 0) {
    if (!BIO_should_retry(_bio)) {
      // Handle failed read here.
    }

    // Do something to handle the retry.
  }

  return bytesRead;
}

int Socket::Write(const char* buffer, int bufferSize) {
  int bytesWritten = BIO_write(_bio, buffer, bufferSize);
  if (bytesWritten <= 0) {
    if (!BIO_should_retry(_bio)) {
      // Handle failed writes here.
    }

    // Do something to handle the retry.
  }

  return bytesWritten;
}

bool Socket::DoConnect(const std::string& connectionString) {
  _bio = BIO_new_connect(const_cast<char*>(connectionString.c_str()));
  if (_bio == nullptr) {
    std::cerr << "ERROR: Could not create connection." << std::endl;
    return false;
  }

  long connectResult = BIO_do_connect(_bio);
  if (connectResult <= 0) {
    std::cerr << "ERROR: Could not connect to \"" << connectionString << "\"."
              << std::endl;
    return false;
  }

  return true;
}

}  // namespace net
