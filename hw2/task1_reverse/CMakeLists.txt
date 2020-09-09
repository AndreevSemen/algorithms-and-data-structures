add_executable(reverse_unittests
        ${CMAKE_CURRENT_SOURCE_DIR}/reverse_unittests.cpp
)

target_include_directories(reverse_unittests
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(reverse_unittests
        PUBLIC GTest::main
)
