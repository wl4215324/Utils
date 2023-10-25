cmake_minimum_required(VERSION 3.4)
project(epoll_timer LANGUAGES CXX)

# set(TARGET_NAME ref_test)
# file(GLOB_RECURSE APPLICATION_SRCS ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
# AUX_SOURCE_DIRECTORY(. DIR_SRCS)

set(TARGET_NAME epoll_timer_test)
file(GLOB APPLICATION_SRCS ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
add_executable(${TARGET_NAME} ${APPLICATION_SRCS})
target_link_libraries(${TARGET_NAME} pthread)
install(TARGETS ${TARGET_NAME} DESTINATION bin)