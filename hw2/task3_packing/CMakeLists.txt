add_library(deck_packing STATIC
        ${CMAKE_CURRENT_SOURCE_DIR}/deck_packing.cpp
)
target_include_directories(deck_packing
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)

add_executable(deck_packing_unittests
        ${CMAKE_CURRENT_SOURCE_DIR}/deck_packing_unittests.cpp
)
target_include_directories(deck_packing_unittests
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)
target_link_libraries(deck_packing_unittests
        PUBLIC GTest::main
        PUBLIC deck_packing
)
