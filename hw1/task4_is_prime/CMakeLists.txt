add_library(is_prime STATIC
        ${CMAKE_CURRENT_SOURCE_DIR}/is_prime.cpp
)
target_include_directories(is_prime
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)

add_executable(is_prime_unittests
        ${CMAKE_CURRENT_SOURCE_DIR}/is_prime_unittests.cpp
)
target_link_libraries(is_prime_unittests
        PUBLIC GTest::main
        PUBLIC is_prime
)
