project(advanced_shm LANGUAGES CXX)

set(TARGET_NAME advanced_shm_read_test)

# 生成库的源码文件
file(GLOB COMMON_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)

add_executable(${TARGET_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/src/test/shm_read_test.cpp ${COMMON_SRCS})

target_include_directories(${TARGET_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

target_link_libraries(${TARGET_NAME} pthread)

install(TARGETS ${TARGET_NAME} DESTINATION bin)

unset(TARGET_NAME)
set(TARGET_NAME advanced_shm_write_test)
# 生成库的源码文件
file(GLOB COMMON_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)

add_executable(${TARGET_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/src/test/shm_write_test.cpp ${COMMON_SRCS})
target_include_directories(${TARGET_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_link_libraries(${TARGET_NAME} pthread)
install(TARGETS ${TARGET_NAME} DESTINATION bin)