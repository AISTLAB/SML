cmake_minimum_required(VERSION 3.6)
project(SML)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=std")

set(SOURCE_FILES
        sml_v4.c)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")
add_executable(SML ${SOURCE_FILES})