cmake_minimum_required(VERSION 2.6)
project(bloom)

#SET (EXECUTABLE_OUTPUT_PATH
#   ${PROJECT_BINARY_DIR}
#   CACHE PATH
#   "Single Directory for all Executables."
#   )

set(CMAKE_CXX_FLAGS "-g -std=c++14 -O2  -O2  -O2  -O2  -O2 -pedantic -Wall -Wextra -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-declarations -Wmissing-include-dirs -Wnoexcept -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 -Wswitch-default -Wundef -Werror -Wno-unused")

# documentation
add_subdirectory(doc)

# tests
add_subdirectory(tests)
