cmake_minimum_required(VERSION 3.10)

project(lestrutter)

set(TARGET_ARCHITECTURE x64)
set(CMAKE_CXX_STANDARD 17)

add_definitions(-DSOURCE_PATH="${CMAKE_SOURCE_DIR}")

find_library(SDL2_LIBRARY
  NAMES SDL2
  HINTS
    dependencies
  PATH_SUFFIXES lib
)
find_library(SDL2_LIBRARY_MAIN
  NAMES SDL2MAIN
  HINTS
    dependencies
  PATH_SUFFIXES lib
)

find_path(SDL2_INCLUDE_DIR SDL.h
  HINTS
    include
  PATH_SUFFIXES SDL2
)

add_executable(lestrutter
    src/main.cpp
    src/camera.cpp
    src/ol_mesh.cpp
    src/glad.c

    src/shader.h
    src/camera.h
    src/ol_mesh.h
)

target_include_directories(lestrutter PUBLIC ${SDL2_INCLUDE_DIR} include/)
target_link_libraries(lestrutter ${SDL2_LIBRARY} ${SDL2_LIBRARY_MAIN})