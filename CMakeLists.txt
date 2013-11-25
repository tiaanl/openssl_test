cmake_minimum_required(VERSION 2.8)

project("openssl_test")

set(OPENSSL_ROOT "" CACHE PATH "Path to root of OpenSSL")

include_directories("${OPENSSL_ROOT}/include")

add_executable("openssl_test"
  "src/client_socket.cpp"
  "src/client_socket.h"
  "src/main.cpp"
  "src/scoped_openssl.h"
  "src/socket.cpp"
  "src/socket.h"
  "src/client_ssl_socket.cpp"
  "src/client_ssl_socket.h"
)

target_link_libraries("openssl_test"
  "${OPENSSL_ROOT}/lib/libeay32.lib"
  "${OPENSSL_ROOT}/lib/ssleay32.lib"
  "ws2_32.lib"
)
