// OpenSSLTest

#include "client_ssl_socket.h"

#include <cassert>
#include <iostream>
#include <openssl/err.h>
#include <openssl/bio.h>

namespace net {

ClientSSLSocket::ClientSSLSocket() {}

ClientSSLSocket::~ClientSSLSocket() {}

bool ClientSSLSocket::Connect(std::string hostAndPort) {
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
  BIO_set_conn_hostname(_bio.Get(), hostAndPort.c_str());
  
  if (BIO_do_connect(_bio.Get()) <= 0) {
    std::cerr << "ERROR: Could not connect to \"" << hostAndPort << "\""
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

void ClientSSLSocket::Disconnect() {
  _ctx.Reset(nullptr);
  _bio.Reset(nullptr);
}

bool ClientSSLSocket::Read(char* buffer, int bufferSize, int* bytesRead) {
  assert(buffer);
  assert(bufferSize > 0);

  SSL* ssl = nullptr;
  BIO_get_ssl(_bio.Get(), &ssl);

  int rv = SSL_read(ssl, buffer, bufferSize);

  if (bytesRead)
    *bytesRead = (rv <= 0) ? 0 : rv;

  if (rv <= 0) {
    if (rv == 0 && BIO_should_retry(_bio.Get()))
      return Read(buffer, bufferSize, bytesRead);
    return false;
  }

  return true;
}

bool ClientSSLSocket::Write(const char* buffer, int bufferSize,
                            int* bytesWritten) {
  assert(buffer);
  assert(bufferSize > 0);

  SSL* ssl = nullptr;
  BIO_get_ssl(_bio.Get(), &ssl);

  int rv = SSL_write(ssl, buffer, bufferSize);

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
