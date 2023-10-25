cmake_minimum_required(VERSION 3.4)

project(CXX_utils LANGUAGES CXX)

# SET(CMAKE_C_COMPILER /usr/bin/gcc)
# SET(CMAKE_CXX_COMPILER /usr/bin/g++)

SET(CMAKE_C_COMPILER $ENV{gcc})
SET(CMAKE_CXX_COMPILER $ENV{g++})

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_BUILD_TYPE Release)

add_subdirectory(ShareMemory)
add_subdirectory(demo1)
add_subdirectory(epollTimer-main)

set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}_install/)
