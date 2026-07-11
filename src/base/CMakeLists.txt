add_library(mycc_base
    base_inc.c
)

target_include_directories(mycc_base
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)
