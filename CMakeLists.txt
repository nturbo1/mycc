cmake_minimum_required(VERSION 3.20)

project(mycc C)

include(cmake/configs.cmake)

add_executable(mycc src/main.c)

add_subdirectory(test)
add_subdirectory(src)

target_link_libraries(mycc
    PRIVATE
        mycc_core
)
