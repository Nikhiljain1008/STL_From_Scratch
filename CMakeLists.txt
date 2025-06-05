cmake_minimum_required(VERSION 3.10)
project(STL_From_Scratch)

set(CMAKE_CXX_STANDARD 17)

# Include headers from the 'include' folder
include_directories(include)

# Add the source file from the 'src' folder
add_executable(main test/main.cpp)
