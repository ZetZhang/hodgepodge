cmake_minimum_required(VERSION 1.1.0)
project(hodgepodge)
include_directories(${PROJECT_SOURCE_DIR})

option(PROJECT_TESTS "Something tests" ON)

set(CMAKE_BUILD_TYPE "Debug")
set(CMKAE_CXX_STANDARD 14)
set(CXX_FLAGS
    -g
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
    # -MMD
    -rdynamic
    )
#set(CMAKE_CXX_FLAGS ${CXX_FLAGS})
string(REPLACE ";" " " CMAKE_CXX_FLAGS "${CXX_FLAGS}")

set(CMAKE_CXX_FLAGS_DEBUG "-O0")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG") # hint assert

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

