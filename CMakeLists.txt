cmake_minimum_required(VERSION 3.0)
project(cross_road)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

file(GLOB_RECURSE PROJECT_SOURCES "src/*.cpp")
file(GLOB_RECURSE PROJECT_HEADERS "include/*.hpp")

set(PROJECT_INCLUDE_DIRS "")
foreach(_headerFile ${PROJECT_HEADERS})
    get_filename_component(_dir ${_headerFile} PATH)
    list (APPEND PROJECT_INCLUDE_DIRS ${_dir})

endforeach()

list(REMOVE_DUPLICATES PROJECT_INCLUDE_DIRS)

add_executable(cross_road ${PROJECT_SOURCES})

set_target_properties(cross_road PROPERTIES
            CXX_STANDARD 17
            CXX_EXTENSIONS OFF)

target_link_libraries(cross_road
    ${SDL2_LIBRARY}
    ${SDL2_IMAGE_LIBRARIES}
)