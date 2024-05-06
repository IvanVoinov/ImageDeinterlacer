cmake_minimum_required(VERSION 3.12)
project(picture_deinterlacer VERSION 0.1.0 LANGUAGES C CXX)


include(ExternalProject)

ExternalProject_Add(
    libjpeg
    GIT_REPOSITORY https://github.com/LuaDist/libjpeg.git
    GIT_TAG master
    PREFIX ${CMAKE_BINARY_DIR}/libjpeg
    INSTALL_DIR ${CMAKE_BINARY_DIR}/libjpeg
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=<INSTALL_DIR>
)

add_executable(picture_deinterlacer
    main.cpp
    source/private/FileManager.cpp
    source/private/ImageProcessor.cpp
)

set_target_properties(
    picture_deinterlacer PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

# Specify the include directory for libjpeg
ExternalProject_Get_Property(libjpeg SOURCE_DIR)
target_include_directories(picture_deinterlacer PRIVATE ${SOURCE_DIR})

# Specify the link directory for libjpeg
ExternalProject_Get_Property(libjpeg BINARY_DIR)
target_link_directories(picture_deinterlacer PRIVATE ${BINARY_DIR})

target_link_libraries(picture_deinterlacer PRIVATE jpeg)

add_dependencies(picture_deinterlacer libjpeg)
