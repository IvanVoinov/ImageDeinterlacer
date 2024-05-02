cmake_minimum_required(VERSION 3.12)
project(picture_deinterlacer VERSION 0.1.0 LANGUAGES C CXX)

include(FetchContent)

FetchContent_Declare(
    lib_jpeg
    GIT_REPOSITORY https://github.com/LuaDist/libjpeg.git
    GIT_TAG        6c0fcb8ddee365e7abc4d332662b06900612e923
    OVERRIDE_FIND_PACKAGE
)

set(FETCHCONTENT_BASE_DIR ${PROJECT_SOURCE_DIR}/third_party CACHE PATH "Missing description." FORCE)

find_package(lib_jpeg)

add_executable(picture_deinterlacer main.cpp)

target_link_libraries(picture_deinterlacer PRIVATE jpeg)