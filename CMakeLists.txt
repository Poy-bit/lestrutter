cmake_minimum_required(VERSION 3.10)

project(lestrutter)

set(TARGET_ARCHITECTURE x64)
set(CMAKE_CXX_STANDARD 17)

add_definitions(-DSOURCE_PATH="${CMAKE_SOURCE_DIR}")

find_library(SDL2_LIBRARY
  NAMES SDL2
  HINTS
    dependencies/libraries/SDL2
  PATH_SUFFIXES lib
)
find_library(SDL2_LIBRARY_MAIN
  NAMES SDL2MAIN
  HINTS
    dependencies/libraries/SDL2
  PATH_SUFFIXES lib
)

find_path(SDL2_INCLUDE_DIR SDL.h
  HINTS
    dependencies/libraries
  PATH_SUFFIXES SDL2
)

add_executable(lestrutter
    src/main.cpp
    src/camera.cpp
    src/ol_mesh.cpp
    src/collider.cpp
    src/glad.c

    include/shader.h
    include/camera.h
    include/ol_mesh.h
    include/rigidbody.h
    include/collider.h
    include/physics.h
    include/mathtypes.h
    include/aabb.h
)

target_include_directories(lestrutter PUBLIC ${SDL2_INCLUDE_DIR} dependencies/libraries include/ dependencies/libraries/stb)
target_link_libraries(lestrutter ${SDL2_LIBRARY} ${SDL2_LIBRARY_MAIN})