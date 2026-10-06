cmake_minimum_required(VERSION 3.16)
project(Sweeppp CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

add_subdirectory(vendors/SDL EXCLUDE_FROM_ALL)
add_subdirectory(vendors/SDL_image EXCLUDE_FROM_ALL)

file(GLOB_RECURSE SWEEPPP_SOURCES CONFIGURE_DEPENDS src/*.cc)
add_executable(sweeppp ${SWEEPPP_SOURCES})
target_include_directories(sweeppp PRIVATE src)

target_link_libraries(sweeppp PRIVATE SDL3::SDL3 SDL3_image::SDL3_image)