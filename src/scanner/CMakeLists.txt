target_sources(mycc_core
    PUBLIC
    scanner.c
    numbers.c
)

target_sources(mycc_test
    PRIVATE
    scanner_test.c
)
