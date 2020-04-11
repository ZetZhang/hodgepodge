#set(CMAKE_C_COMPILER /usr/bin/clang)
set(CMAKE_C_COMPILER /usr/bin/gcc)
#set(CMAKE_CXX_COMPILER /usr/bin/clang++)
set(CMAKE_CXX_COMPILER "/usr/bin/g++")
# project
project(hodgepodge)
cmake_minimum_required(VERSION 1.1.0)
include_directories(${PROJECT_SOURCE_DIR})


option(PROJECT_TESTS "Something tests" ON)
set(CMAKE_BUILD_TYPE "Debug")

set(CMAKE_C_FLAGS -Wall -Werror -Wextra)
set(CMAKE_C_FLAGS_DEBUG "-O2 -g")
set(CMAKE_C_FLAGS_RELEASE "-O4 -DNDEBUG")

set(CMKAE_CXX_STANDARD 14)
set(CXX_FLAGS
    -DCHECK_PTHREAD_RETURN_VALUE
    -D_FILE_OFFSET_BITS=64
    -Wall
    -Wextra
    -Werror
    -Wconversion
    -Wno-unused-parameter
    -Wold-style-cast
    -Woverloaded-virtual
    -Wpointer-arith
    -Wshadow
    -Wwrite-strings
    -march=native
    -Winline
    -Wcast-qual
    -Wunreachable-code
    #-Waggregate-return

    -Wno-unused-variable
    -Wno-format-truncation
    # -MMD
    -rdynamic
    )
if(CMAKE_BUILD_BITS EQUAL 32)
    list(APPEND CXX_FLAGS -m32)
endif()

if(CMAKE_CXX_COMPILER_ID MATCHES Clang)
    message(STATUS ${CMAKE_CXX_COMPILER_ID})
    # APPEND
    list(APPEND CXX_FLAGS -Wno-sign-conversion)
    list(APPEND CXX_FLAGS -W)
    # REMOVE
    list(REMOVE_ITEM CXX_FLAGS -Wno-format-truncation)
    list(REMOVE_ITEM CXX_FLAGS -rdynamic)
    # set
    list(APPEND CXX_FLAGS -Wno-unused-parameter)
endif()

string(REPLACE ";" " " CMAKE_CXX_FLAGS "${CXX_FLAGS}")

set(CMAKE_CXX_FLAGS_DEBUG "-O2 -g")
set(CMAKE_CXX_FLAGS_RELEASE "-O4 -DNDEBUG") # hint assert

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
message(STATUS "bin outputed")
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)
message(STATUS "lib outputed")

enable_testing()
#set_tests_properties
add_subdirectory(hdgd/base)
#add_subdirectory(hdgd/logging)
#add_subdirectory(hdgd/steal)
#add_subdirectory(hdgd/thread)

# target link
# make library(.os or .a)
# make test
# total execute

