enable_testing()

SET (CTEST_BINARY_DIRECTORY
    ${PROJECT_BINARY_DIR})

add_executable(test_int test_int.cpp)
add_test(integer_filter test_int)

add_executable(test_str test_string.cpp)
add_test(string_filter test_str)

add_executable(test_char test_char.cpp)
add_test(char_filter test_char)
