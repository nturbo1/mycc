add_library(mycc_core
    compiler.c
    error.c
    scanner.c
    token.c
)

target_link_libraries(mycc_core
    compiler_warnings
    m # math library
    mycc_core_util
)

add_library(mycc_core_util
    util/darray.c
    util/hashtable.c
)

target_include_directories(mycc_core_util
    PUBLIC
        include
)

target_sources(mycc_test
    PRIVATE
    util/darray_test.c
    util/hashtable_test.c
    scanner_test.c
)
target_include_directories(mycc_test
    PRIVATE
    include
)
target_link_libraries(mycc_test
    PRIVATE
    mycc_core
    mycc_core_util
)
