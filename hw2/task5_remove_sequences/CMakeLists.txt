add_executable(remove_sequences_unittests
        ${CMAKE_CURRENT_SOURCE_DIR}/remove_sequences_unittests.cpp
)
target_include_directories(remove_sequences_unittests
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)
target_link_libraries(remove_sequences_unittests
        PUBLIC GTest::main
)
