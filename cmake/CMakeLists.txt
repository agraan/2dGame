cmake_minimum_required(VERSION 3.22)
project(MyGameProject)

# === Project Setup ===
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(OPENGL_GL_PREFERENCE GLVND)

# === Dependencies ===
find_package(OpenGL REQUIRED)
find_package(SDL2 REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL2IMAGE REQUIRED SDL2_image)
find_package(GLEW REQUIRED)

#=== Source Directory ===
set(SRC_DIR ${CMAKE_SOURCE_DIR}/../src)

# === Source Files ===
file(GLOB_RECURSE GAME_SOURCES
	${SRC_DIR}/*.cpp
)

# === Executable ===
add_executable(MyGame ${GAME_SOURCES})

# === Include Paths ===
target_include_directories(MyGame PRIVATE
	${CMAKE_SOURCE_DIR}/../include
	${SDL2_INCLUDE_DIRS}
	${SDL2_IMAGE_INCLUDE_DIRS}
	${GLEW_INCLUDE_DIRS}
)


# === Link Libraries ===
target_link_libraries(MyGame PRIVATE
    SDL2::SDL2
    GLEW::GLEW
    OpenGL::GL
	${SDL2IMAGE_LIBRARIES}
)

# === Output Directories ===
set_target_properties(MyGame PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}
)

