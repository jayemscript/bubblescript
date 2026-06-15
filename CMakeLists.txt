cmake_minimum_required(VERSION 3.20)
project(bubblescript LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON) 

if(WIN32)
    set(CMAKE_EXE_LINKER_FLAGS "-static -static-libgcc -static-libstdc++")
endif()

# Modules
add_executable(
    bubblescript
    src/main.cpp

    # interpreter
    src/interpreter/interpreter.cpp
    src/interpreter/variables.cpp
)

target_include_directories(
    bubblescript
    PRIVATE
    src
)

# Tests
option(BUILD_TESTS "Build tests" ON)
if(BUILD_TESTS)
    enable_testing()
endif()