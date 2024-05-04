cmake_minimum_required(VERSION 3.12)
project(picture_deinterlacer VERSION 0.1.0 LANGUAGES C CXX)

# include(FetchContent)

# FetchContent_Declare(
#     lib_jpeg
#     GIT_REPOSITORY https://github.com/LuaDist/libjpeg.git
#     GIT_TAG        6c0fcb8ddee365e7abc4d332662b06900612e923
#     OVERRIDE_FIND_PACKAGE
# )

# set(FETCHCONTENT_BASE_DIR ${PROJECT_SOURCE_DIR}/third_party CACHE PATH "Missing description." FORCE)

# find_package(lib_jpeg PATHS ${PROJECT_SOURCE_DIR})

# add_executable(picture_deinterlacer main.cpp)

# target_link_libraries(picture_deinterlacer PRIVATE jpeg)


set(REPO_URL "https://github.com/LuaDist/libjpeg.git")
set(REPO_DIR ${CMAKE_SOURCE_DIR}/third_party/lib_jpeg)

if(NOT EXISTS ${REPO_DIR})
    execute_process(
        COMMAND git clone ${REPO_URL} ${REPO_DIR}
        RESULT_VARIABLE GIT_RESULT
    )

    if (NOT GIT_RESULT EQUAL "0")
        message(FATAL_ERROR "Failed to clone libjpeg repo.")
    endif()
endif()

add_executable(picture_deinterlacer
    main.cpp
    source/private/FileManager.cpp
    source/private/ImageProcessor.cpp
)

add_subdirectory(${REPO_DIR})

target_link_libraries(picture_deinterlacer jpeg)