# Install script for directory: /home/jp/git/obs-websocket

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
  if(EXISTS "$ENV{DESTDIR}/usr/local/lib/obs-plugins/obs-websocket.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/local/lib/obs-plugins/obs-websocket.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}/usr/local/lib/obs-plugins/obs-websocket.so"
         RPATH "")
  endif()
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/lib/obs-plugins/obs-websocket.so")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/usr/local/lib/obs-plugins" TYPE MODULE FILES "/home/jp/git/obs-websocket/build/obs-websocket.so")
  if(EXISTS "$ENV{DESTDIR}/usr/local/lib/obs-plugins/obs-websocket.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/local/lib/obs-plugins/obs-websocket.so")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}/usr/local/lib/obs-plugins/obs-websocket.so")
    endif()
  endif()
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/share/obs/obs-plugins/obs-websocket/locale/de-DE.ini;/usr/local/share/obs/obs-plugins/obs-websocket/locale/it-IT.ini;/usr/local/share/obs/obs-plugins/obs-websocket/locale/es-ES.ini;/usr/local/share/obs/obs-plugins/obs-websocket/locale/nl-NL.ini;/usr/local/share/obs/obs-plugins/obs-websocket/locale/zh-TW.ini;/usr/local/share/obs/obs-plugins/obs-websocket/locale/en-US.ini;/usr/local/share/obs/obs-plugins/obs-websocket/locale/ja-JP.ini;/usr/local/share/obs/obs-plugins/obs-websocket/locale/ru-RU.ini;/usr/local/share/obs/obs-plugins/obs-websocket/locale/pl-PL.ini;/usr/local/share/obs/obs-plugins/obs-websocket/locale/zh-CN.ini;/usr/local/share/obs/obs-plugins/obs-websocket/locale/fr-FR.ini;/usr/local/share/obs/obs-plugins/obs-websocket/locale/pt-BR.ini;/usr/local/share/obs/obs-plugins/obs-websocket/locale/pt-PT.ini;/usr/local/share/obs/obs-plugins/obs-websocket/locale/ko-KR.ini")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/usr/local/share/obs/obs-plugins/obs-websocket/locale" TYPE FILE FILES
    "/home/jp/git/obs-websocket/data/locale/de-DE.ini"
    "/home/jp/git/obs-websocket/data/locale/it-IT.ini"
    "/home/jp/git/obs-websocket/data/locale/es-ES.ini"
    "/home/jp/git/obs-websocket/data/locale/nl-NL.ini"
    "/home/jp/git/obs-websocket/data/locale/zh-TW.ini"
    "/home/jp/git/obs-websocket/data/locale/en-US.ini"
    "/home/jp/git/obs-websocket/data/locale/ja-JP.ini"
    "/home/jp/git/obs-websocket/data/locale/ru-RU.ini"
    "/home/jp/git/obs-websocket/data/locale/pl-PL.ini"
    "/home/jp/git/obs-websocket/data/locale/zh-CN.ini"
    "/home/jp/git/obs-websocket/data/locale/fr-FR.ini"
    "/home/jp/git/obs-websocket/data/locale/pt-BR.ini"
    "/home/jp/git/obs-websocket/data/locale/pt-PT.ini"
    "/home/jp/git/obs-websocket/data/locale/ko-KR.ini"
    )
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.

endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/home/jp/git/obs-websocket/build/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
