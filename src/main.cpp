// OpenSSLTest

#include "ssl_socket.h"
#include <crtdbg.h>
#include <openssl/bio.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <cstdio>

int Run() {
  // Initialize OpenSSL
  ERR_load_BIO_strings();
  SSL_load_error_strings();
  OpenSSL_add_all_algorithms();

  net::SSLSocket socket;
  if (!socket.Connect("www.verisign.com", 443))
    return 1;

  std::stringstream requestStream;
  requestStream << "GET / HTTP/1.0\r\n"
                << "Host: www.verisign.com\r\n"
                << "\r\n";

  std::string requestData(requestStream.str());
  int bytesWritten = socket.Write(requestData.data(), requestData.size());
  if (bytesWritten <= 0)
    return 1;

  std::vector<char> responseBuffer(4096, 0);

  for (;;) {
    int bytesRead = socket.Read(responseBuffer.data(), responseBuffer.size() - 1);
    if (bytesRead <= 0)
      break;
    responseBuffer[bytesRead] = '\0';
    std::cout << responseBuffer.data() << std::endl;
  }

  return 0;
}

int main() {
  int result = Run();

  _CrtDumpMemoryLeaks();

  return result;
}
