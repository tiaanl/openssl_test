// OpenSSLTest

#include "socket.h"
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
  SSL_load_error_strings();
  ERR_load_BIO_strings();
  OpenSSL_add_all_algorithms();

  net::Socket socket;
  if (!socket.Connect("localhost", 80))
    return 1;

  std::stringstream requestStream;
  requestStream << "GET / HTTP/1.0\n"
                << "Server: ubuntu-build.playsafesa.com\n"
                << "\n";

  std::string requestData(requestStream.str());
  int bytesWritten = socket.Write(requestData.data(), requestData.size());
  if (bytesWritten <= 0)
    return 1;

  std::vector<char> responseBuffer(4096, 0);
  int bytesRead = socket.Read(responseBuffer.data(), responseBuffer.size());
  std::cout << responseBuffer.data() << std::endl;

  return 0;
}

int main() {
  int result = Run();

  _CrtDumpMemoryLeaks();

  return result;
}
