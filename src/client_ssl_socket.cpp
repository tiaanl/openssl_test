// OpenSSLTest

#include "client_ssl_socket.h"

#include <cassert>
#include <iostream>
#include <openssl/err.h>
#include <openssl/bio.h>

namespace net {

ClientSSLSocket::ClientSSLSocket() : ClientSocket() {}

ClientSSLSocket::~ClientSSLSocket() {}

bool ClientSSLSocket::DoConnect(const std::string& connectionString) {
  SSL_library_init();
  _ctx.Reset(SSL_CTX_new(SSLv23_client_method()));
  if (!_ctx.Get()) {
    ERR_print_errors_fp(stderr);
    return false;
  }

  _bio.Reset(BIO_new_ssl_connect(_ctx.Get()));

  SSL* ssl = nullptr;

  // Set some flags.
  BIO_get_ssl(_bio.Get(), &ssl);
  SSL_set_mode(ssl, SSL_MODE_AUTO_RETRY);

  // Create and setup the connection.
  BIO_set_conn_hostname(_bio.Get(), connectionString.c_str());
  
  if (BIO_do_connect(_bio.Get()) <= 0) {
    std::cerr << "ERROR: Could not connect to \"" << connectionString << "\""
              << std::endl;
    ERR_print_errors_fp(stderr);
    return false;
  }

#if 0  // We don't care about the certificate validity at the moment.
  // Check the certificate.
  if (SSL_get_verify_result(ssl) != X509_V_OK) {
    std::cerr << "ERROR: Certificate verification error ("
              << SSL_get_verify_result(ssl) << ")" << std::endl;
    ERR_print_errors_fp(stderr);
    return false;
  }
#endif  // 0

  return true;
}

void ClientSSLSocket::DoDisconnect() {
  _ctx.Reset(nullptr);
  ClientSocket::DoDisconnect();
}

int ClientSSLSocket::DoRead(char* buffer, int bufferSize) {
  assert(bufferSize > 0);

  SSL* ssl = nullptr;
  BIO_get_ssl(_bio.Get(), &ssl);

  int bytesRead = SSL_read(ssl, buffer, bufferSize);
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

int ClientSSLSocket::DoWrite(const char* buffer, int bufferSize) {
  assert(bufferSize > 0);

  SSL* ssl = nullptr;
  BIO_get_ssl(_bio.Get(), &ssl);

  int bytesWritten = SSL_write(ssl, buffer, bufferSize);
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