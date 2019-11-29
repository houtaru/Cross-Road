file(GLOB_RECURSE TEST_SOURCES "${PROJECT_SOURCE_DIR}/test/*.cpp")

add_executable(unit_tests ${TEST_SOURCES})

set_target_properties(unit_tests PROPERTIES
    CXX_STANDARD 17
    CXX_EXTENSIONS OFF
)

target_link_libraries(unit_tests
    ${SDL2_LIBRARY}
    ${SDL2_IMAGE_LIBRARY}
    ${SDL2_TTF_LIBRARY}
    ${SDL2_MIXER_LIBRARY}
    gtest_main
    gtest
    gmock
)

add_test(
    NAME unit
    COMMAND
    ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}/unit_tests
)
