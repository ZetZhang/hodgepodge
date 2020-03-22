set(BASE_SRCS
    ./color.cpp
    ./logging.cpp
    ./prompt.cpp
    ./timestamp.cpp
    )

add_library(hdgd_base ${BASE_SRCS})

target_link_libraries(hdgd_base pthread)

file(GLOB HEADERS "*.h")
list(APPEND HEADERS "ename.c.inc")

install(TARGETS hdgd_base DESTINATION lib)
install(FILES ${HEADERS} DESTINATION include/hdgd/base)

#set(FLAG $ENV{_TERROR_SWITCH})
#if (FLAG)

add_subdirectory(tests)
