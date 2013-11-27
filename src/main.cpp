// OpenSSLTest

#include <memory>
#include <sstream>
#include <vector>
#include <iostream>

#include <crtdbg.h>
#include <openssl/bio.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

#include "client_ssl_socket.h"
#include "client_tcp_socket.h"

int Run() {
  // Initialize OpenSSL
  ERR_load_BIO_strings();
  SSL_load_error_strings();
  OpenSSL_add_all_algorithms();

#if 0
  std::unique_ptr<net::ClientTCPSocket> socket(new net::ClientTCPSocket());
  if (!socket->Connect("www.verisign.com:80"))
    return 1;
#else
  std::unique_ptr<net::ClientSSLSocket> socket(new net::ClientSSLSocket());
  if (!socket->Connect("www.verisign.com:443"))
    return 1;
#endif

  std::stringstream requestStream;
  requestStream << "GET / HTTP/1.0\r\n"
                << "Host: www.verisign.com\r\n"
                << "\r\n";

  std::string requestData(requestStream.str());
  int bytesWritten = 0;
  if (!socket->Write(requestData.data(), requestData.size(), &bytesWritten))
    return 1;

  std::vector<char> responseBuffer(4096, 0);

  for (;;) {
    int bytesRead = 0;
    if (!socket->Read(responseBuffer.data(), responseBuffer.size() - 1, &bytesRead))
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
