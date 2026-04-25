add_library(mycc_core_util
    darray.c
    hashtable.c
)
target_include_directories(mycc_core_util
    PUBLIC
        include
    PRIVATE
        ${CMAKE_SOURCE_DIR}/src/include
)

target_sources(mycc_test
    PRIVATE
    darray_test.c
    hashtable_test.c
)
