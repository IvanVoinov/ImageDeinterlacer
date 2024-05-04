cmake_minimum_required(VERSION 3.12)
project(picture_deinterlacer VERSION 0.1.0 LANGUAGES C CXX)


include(ExternalProject)

# Download and build libjpeg as an external project
ExternalProject_Add(
    libjpeg
    GIT_REPOSITORY https://github.com/LuaDist/libjpeg.git
    GIT_TAG master  # Or specify a specific version/tag
    PREFIX ${CMAKE_BINARY_DIR}/libjpeg
    INSTALL_DIR ${CMAKE_BINARY_DIR}/libjpeg
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=<INSTALL_DIR>
)

# Define a library or executable target for your project
add_executable(picture_deinterlacer
    main.cpp
    source/private/FileManager.cpp
    source/private/ImageProcessor.cpp
)

# Specify the include directory for libjpeg
ExternalProject_Get_Property(libjpeg SOURCE_DIR)
target_include_directories(picture_deinterlacer PRIVATE ${SOURCE_DIR})

# Specify the link directory for libjpeg
ExternalProject_Get_Property(libjpeg BINARY_DIR)
target_link_directories(picture_deinterlacer PRIVATE ${BINARY_DIR})

# Link your project against libjpeg
target_link_libraries(picture_deinterlacer PRIVATE jpeg)

# Specify dependencies for your executable (optional)
add_dependencies(picture_deinterlacer libjpeg)
