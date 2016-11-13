cmake_minimum_required(VERSION 3.6)
project(SML)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c11")

set(SOURCE_FILES
        sml_v3.c)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")
add_executable(SML ${SOURCE_FILES})