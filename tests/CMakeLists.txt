enable_testing()

SET (CTEST_BINARY_DIRECTORY
    ${PROJECT_BINARY_DIR})

add_executable(test_int test_int.cpp)

add_test(integer_filter test_int)
