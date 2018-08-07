# Install script for directory: /home/jp/git/obs-websocket/deps/mbedtls/include

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mbedtls" TYPE FILE PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ WORLD_READ FILES
    "/home/jp/git/obs-websocket/deps/mbedtls/include/mbedtls/sha512.h"
    "/home/jp/git/obs-websocket/deps/mbedtls/include/mbedtls/md2.h"
    "/home/jp/git/obs-websocket/deps/mbedtls/include/mbedtls/x509_crt.h"
    "/home/jp/git/obs-websocket/deps/mbedtls/include/mbedtls/pkcs12.h"
    "/home/jp/git/obs-websocket/deps/mbedtls/include/mbedtls/check_config.h"
    "/home/jp/git/obs-websocket/deps/mbedtls/include/mbedtls/debug.h"
    "/home/jp/git/obs-websocket/deps/mbedtls/include/mbedtls/bn_mul.h"
    "/home/jp/git/obs-websocket/deps/mbedtls/include/mbedtls/entropy.h"
    "/home/jp/git/obs-websocket/deps/mbedtls/include/mbedtls/ssl_cookie.h"
    "/home/jp/git/obs-websocket/deps/mbedtls/include/mbedtls/rsa.h"
    "/home/jp/git/obs-websocket/deps/mbedtls/include/mbedtls/x509.h"
    "/home/jp/git/obs-websocket/deps/mbedtls/include/mbedtls/ctr_drbg.h"
    "/home/jp/git/obs-websocket/deps/mbedtls/include/mbedtls/entropy_poll.h"
    "/home/jp/git/obs-websocket/deps/mbedtls/include/mbedtls/pkcs11.h"
    "/home/jp/git/obs-websocket/deps/mbedtls/include/mbedtls/net_sockets.h"
    "/home/jp/git/obs-websocket/deps/mbedtls/include/mbedtls/memory_buffer_alloc.h"
    "/home/jp/git/obs-websocket/deps/mbedtls/include/mbedtls/timing.h"
    "/home/jp/git/obs-websocket/deps/mbedtls/include/mbedtls/md4.h"
    "/home/jp/git/obs-websocket/deps/mbedtls/include/mbedtls/platform.h"
    "/home/jp/git/obs-websocket/deps/mbedtls/include/mbedtls/ecdh.h"
    "/home/jp/git/obs-websocket/deps/mbedtls/include/mbedtls/pkcs5.h"
    "/home/jp/git/obs-websocket/deps/mbedtls/include/mbedtls/oid.h"
    "/home/jp/git/obs-websocket/deps/mbedtls/include/mbedtls/md.h"
    "/home/jp/git/obs-websocket/deps/mbedtls/include/mbedtls/ecjpake.h"
    "/home/jp/git/obs-websocket/deps/mbedtls/include/mbedtls/ssl_ciphersuites.h"
    "/home/jp/git/obs-websocket/deps/mbedtls/include/mbedtls/md5.h"
    "/home/jp/git/obs-websocket/deps/mbedtls/include/mbedtls/base64.h"
    "/home/jp/git/obs-websocket/deps/mbedtls/include/mbedtls/ccm.h"
    "/home/jp/git/obs-websocket/deps/mbedtls/include/mbedtls/dhm.h"
    "/home/jp/git/obs-websocket/deps/mbedtls/include/mbedtls/ssl_internal.h"
    "/home/jp/git/obs-websocket/deps/mbedtls/include/mbedtls/sha1.h"
    "/home/jp/git/obs-websocket/deps/mbedtls/include/mbedtls/des.h"
    "/home/jp/git/obs-websocket/deps/mbedtls/include/mbedtls/camellia.h"
    "/home/jp/git/obs-websocket/deps/mbedtls/include/mbedtls/hmac_drbg.h"
    "/home/jp/git/obs-websocket/deps/mbedtls/include/mbedtls/pk_internal.h"
    "/home/jp/git/obs-websocket/deps/mbedtls/include/mbedtls/havege.h"
    "/home/jp/git/obs-websocket/deps/mbedtls/include/mbedtls/asn1write.h"
    "/home/jp/git/obs-websocket/deps/mbedtls/include/mbedtls/blowfish.h"
    "/home/jp/git/obs-websocket/deps/mbedtls/include/mbedtls/arc4.h"
    "/home/jp/git/obs-websocket/deps/mbedtls/include/mbedtls/aes.h"
    "/home/jp/git/obs-websocket/deps/mbedtls/include/mbedtls/bignum.h"
    "/home/jp/git/obs-websocket/deps/mbedtls/include/mbedtls/asn1.h"
    "/home/jp/git/obs-websocket/deps/mbedtls/include/mbedtls/certs.h"
    "/home/jp/git/obs-websocket/deps/mbedtls/include/mbedtls/compat-1.3.h"
    "/home/jp/git/obs-websocket/deps/mbedtls/include/mbedtls/ecdsa.h"
    "/home/jp/git/obs-websocket/deps/mbedtls/include/mbedtls/config.h"
    "/home/jp/git/obs-websocket/deps/mbedtls/include/mbedtls/ssl_ticket.h"
    "/home/jp/git/obs-websocket/deps/mbedtls/include/mbedtls/x509_crl.h"
    "/home/jp/git/obs-websocket/deps/mbedtls/include/mbedtls/threading.h"
    "/home/jp/git/obs-websocket/deps/mbedtls/include/mbedtls/cipher.h"
    "/home/jp/git/obs-websocket/deps/mbedtls/include/mbedtls/cipher_internal.h"
    "/home/jp/git/obs-websocket/deps/mbedtls/include/mbedtls/ssl_cache.h"
    "/home/jp/git/obs-websocket/deps/mbedtls/include/mbedtls/platform_time.h"
    "/home/jp/git/obs-websocket/deps/mbedtls/include/mbedtls/ecp.h"
    "/home/jp/git/obs-websocket/deps/mbedtls/include/mbedtls/pem.h"
    "/home/jp/git/obs-websocket/deps/mbedtls/include/mbedtls/x509_csr.h"
    "/home/jp/git/obs-websocket/deps/mbedtls/include/mbedtls/net.h"
    "/home/jp/git/obs-websocket/deps/mbedtls/include/mbedtls/cmac.h"
    "/home/jp/git/obs-websocket/deps/mbedtls/include/mbedtls/ssl.h"
    "/home/jp/git/obs-websocket/deps/mbedtls/include/mbedtls/sha256.h"
    "/home/jp/git/obs-websocket/deps/mbedtls/include/mbedtls/aesni.h"
    "/home/jp/git/obs-websocket/deps/mbedtls/include/mbedtls/ripemd160.h"
    "/home/jp/git/obs-websocket/deps/mbedtls/include/mbedtls/gcm.h"
    "/home/jp/git/obs-websocket/deps/mbedtls/include/mbedtls/padlock.h"
    "/home/jp/git/obs-websocket/deps/mbedtls/include/mbedtls/xtea.h"
    "/home/jp/git/obs-websocket/deps/mbedtls/include/mbedtls/version.h"
    "/home/jp/git/obs-websocket/deps/mbedtls/include/mbedtls/pk.h"
    "/home/jp/git/obs-websocket/deps/mbedtls/include/mbedtls/md_internal.h"
    "/home/jp/git/obs-websocket/deps/mbedtls/include/mbedtls/error.h"
    )
endif()

