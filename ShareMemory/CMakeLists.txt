project(ShareMemory LANGUAGES CXX)

set(TARGET_NAME ShareMemoryTest)

add_subdirectory(advanced_shm)


# 生成库的源码文件
file(GLOB_RECURSE APPLICATION_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/test/*.cpp
)

add_executable(${TARGET_NAME} ${APPLICATION_SRCS})

target_include_directories(${TARGET_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

install(TARGETS ${TARGET_NAME} DESTINATION bin)
