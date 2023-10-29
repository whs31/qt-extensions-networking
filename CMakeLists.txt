cmake_minimum_required(VERSION 3.15)

project(QtExtensionsNetworking
  VERSION 0.0.1
  DESCRIPTION "Qt Extensions Networking Library"
  HOMEPAGE_URL "io.github.whs31"
  LANGUAGES C CXX
)

if(NOT CMAKE_C_STANDARD)
    set(CMAKE_C_STANDARD 17)
    set(CMAKE_C_STANDARD_REQUIRED OFF)
    set(CMAKE_C_EXTENSIONS OFF)
endif(NOT CMAKE_C_STANDARD)

if(NOT CMAKE_CXX_STANDARD)
    set(CMAKE_CXX_STANDARD 17)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
    set(CMAKE_CXX_EXTENSIONS OFF)
endif(NOT CMAKE_CXX_STANDARD)

if(TARGET ${PROJECT_NAME})
    return()
endif()

if(NOT TARGET QtExtensions)
    message(FATAL_ERROR "[Qt Extensions Networking] No Qt Extensions library found.")
endif()

set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOMOC ON)

find_package(QT NAMES Qt5 Qt6 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED
  COMPONENTS
    Core
    Network
)

enable_testing()
include_directories(src/c++ include)

add_library(${PROJECT_NAME} STATIC)
target_sources(${PROJECT_NAME}
  PUBLIC
    include/QtExtensionsNetworking/IConnectable
    include/QtExtensionsNetworking/UDPSocket
    include/QtExtensionsNetworking/NetworkUtils
  PRIVATE
    src/c++/iconnectable.h
    src/c++/udpsocket.h
    src/c++/udpsocket.c++
    src/c++/utils.h
    src/c++/utils.c++
)

target_link_libraries(${PROJECT_NAME}
  PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Network
    QtExtensions
)

target_include_directories(${PROJECT_NAME} PUBLIC include src/c++)