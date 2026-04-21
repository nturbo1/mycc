add_executable(mycc_test)

target_sources(mycc_test
    PRIVATE
    nctest-0.1.0/src/nctest_main.c
)

add_library(nctest
    nctest-0.1.0/src/nctest.c
)
target_include_directories(nctest
    PUBLIC
        nctest-0.1.0/include
)
target_link_libraries(nctest
    PUBLIC
        compiler_warnings
)

target_link_libraries(mycc_test
    PRIVATE
        nctest
)
