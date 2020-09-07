add_executable(permutation_unittests
        ${CMAKE_CURRENT_SOURCE_DIR}/permutation_unittests.cpp
)

target_include_directories(permutation_unittests
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(permutation_unittests
        PUBLIC GTest::main
)
