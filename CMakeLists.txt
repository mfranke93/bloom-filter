cmake_minimum_required(VERSION 2.6)
project(bloom)

#SET (EXECUTABLE_OUTPUT_PATH
#   ${PROJECT_BINARY_DIR}
#   CACHE PATH
#   "Single Directory for all Executables."
#   )

set(CMAKE_CXX_FLAGS "-march=native -g -std=c++17 -O3 -Wall -Wextra")

# documentation
add_subdirectory(doc)

# tests
add_subdirectory(tests)
