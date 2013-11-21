cmake_minimum_required(VERSION 2.8)

project("openssl_test")

set(OPENSSL_ROOT "" CACHE PATH "Path to root of OpenSSL")

include_directories("${OPENSSL_ROOT}/include")

add_executable("openssl_test"
  "src/main.cpp"
  "src/socket.h"
  "src/socket.cpp"
  "src/ssl_socket.h"
  "src/ssl_socket.cpp"
)

target_link_libraries("openssl_test"
  "${OPENSSL_ROOT}/lib/libeay32.lib"
  "${OPENSSL_ROOT}/lib/ssleay32.lib"
)
