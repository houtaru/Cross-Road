file(GLOB_RECURSE PROJECT_SOURCES "${PROJECT_SOURCE_DIR}/src/*.cpp")

add_executable(cross_road ${PROJECT_SOURCES})

set_target_properties(cross_road PROPERTIES
            CXX_STANDARD 17
            CXX_EXTENSIONS OFF
)

target_link_libraries(cross_road
    ${SDL2_LIBRARY}
    ${SDL2_IMAGE_LIBRARY}
    ${SDL2_TTF_LIBRARY}
    ${SDL2_MIXER_LIBRARY}
)

