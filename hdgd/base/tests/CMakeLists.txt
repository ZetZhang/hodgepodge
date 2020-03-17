# execute

add_executable(try_work try_work.cpp)

add_executable(prompt_test prompt_test.cpp)
target_link_libraries(prompt_test hdgd_base)
add_definitions(-D_TMSG)
add_definitions(-D_TFATAL)
add_definitions(-D_TEXIT1)
add_definitions(-D_TEXIT2)
add_definitions(-D_TEXIT3)
add_definitions(-D_TUSAGE)
add_definitions(-DDEBUG)


# unit
add_executable(timestamp_unit_test timestamp_unittest.cpp)
target_link_libraries(timestamp_unit_test hdgd_base)
add_test(NAME timestamp_unit_test COMMAND timestamp_unit_test)

add_executable(color_unit_test color_unittest.cpp)
target_link_libraries(color_unit_test hdgd_base)
add_test(NAME color_unit_test COMMAND color_unit_test)
