add_library(mycc_core
    compiler.c
    error.c
    token.c
)
target_link_libraries(mycc_core
    compiler_warnings
    m # math library
    mycc_core_util
)
target_include_directories(mycc_core
    PUBLIC
    include
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

add_subdirectory(util)
add_subdirectory(scanner)
