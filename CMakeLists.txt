cmake_minimum_required(VERSION 3.10)

project(Blockchain)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_PREFIX_PATH "C:/msys64/mingw64")

find_library(SODIUM_LIB sodium)

add_executable(Blockchain)
target_sources(Blockchain PRIVATE src/main.cpp src/keys.cpp src/common.cpp src/transaction.cpp src/db.cpp)

target_link_libraries(Blockchain ${SODIUM_LIB})
target_link_libraries(Blockchain ${CMAKE_CURRENT_SOURCE_DIR}/lib/libleveldb.a)
target_include_directories(Blockchain PRIVATE include)
target_precompile_headers(Blockchain PRIVATE "include/pch/pch.h")
message(STATUS "Sodium library: ${SODIUM_LIB}")
