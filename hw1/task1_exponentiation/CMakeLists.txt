add_library(exponentiation STATIC
        exponentiation.cpp
)
target_include_directories(exponentiation
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)

add_executable(exponentiation_unittests
        exponentiation_unittests.cpp
)
target_link_libraries(exponentiation_unittests PUBLIC
        GTest::main
        exponentiation
)
