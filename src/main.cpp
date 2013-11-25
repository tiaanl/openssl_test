// OpenSSLTest

#include <cstdio>
#include <iostream>
#include <memory>
#include <string>
#include <sstream>
#include <vector>
#include <crtdbg.h>
#include <openssl/bio.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include "client_ssl_socket.h"

int Run() {
  // Initialize OpenSSL
  ERR_load_BIO_strings();
  SSL_load_error_strings();
  OpenSSL_add_all_algorithms();

  std::unique_ptr<net::ClientSSLSocket> socket(new net::ClientSSLSocket());

#if 0
  if (!socket->Connect("www.verisign.com", 443))
    return 1;

  std::stringstream requestStream;
  requestStream << "GET / HTTP/1.0\r\n"
                << "Host: www.verisign.com\r\n"
                << "\r\n";

  std::string requestData(requestStream.str());
  int bytesWritten = socket->Write(requestData.data(), requestData.size());
  if (bytesWritten <= 0)
    return 1;

  std::vector<char> responseBuffer(4096, 0);

  for (;;) {
    int bytesRead = socket->Read(responseBuffer.data(), responseBuffer.size() - 1);
    if (bytesRead <= 0)
      break;
    responseBuffer[bytesRead] = '\0';
    std::cout << responseBuffer.data() << std::endl;
  }
#endif  // 0

  return 0;
}

int main() {
  int result = Run();

  _CrtDumpMemoryLeaks();

  return result;
}
