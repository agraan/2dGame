cmake_minimum_required(VERSION 3.22)
project(MyGameProject)

# === Project Setup ===
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(OPENGL_GL_PREFERENCE GLVND)

#=== Source Directory ===
set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)

# === Source Files ===
file(GLOB_RECURSE GAME_SOURCES
	${SRC_DIR}/*.cpp
)

# === Dependencies.cmake ===
include(FetchContent)

find_package(OpenGL REQUIRED)

find_package(SDL2 CONFIG QUIET)
if (NOT TARGET SDL2::SDL2)
	FetchContent_Declare(
		SDL2
		GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
		GIT_TAG release-2.30.0
	)
	FetchContent_MakeAvailable(SDL2)
	if (NOT TARGET SDL2::SDL2)
		add_library(SDL2::SDL2 ALIAS SDL2)
	endif()
endif()


find_package(SDL2_image CONFIG QUIET)
if (NOT TARGET SDL2_image::SDL2_image)

	FetchContent_Declare(
		SDL2_image
		GIT_REPOSITORY https://github.com/libsdl-org/SDL_image.git
		GIT_TAG release-2.8.2
	)
	FetchContent_MakeAvailable(SDL2_image)
	if (NOT TARGET SDL2_image::SDL2_image)
		add_library(SDL2_image::SDL2_image ALIAS SDL2_image)
	endif()
endif()

find_package(GLEW REQUIRED)
if (NOT TARGET GLEW::GLEW)
	FetchContent_Declare(
		GLEW
		GIT_REPOSITORY https://github.com/nigels-com/glew.git
		GIT_TAG glew-2.2.0
	)
	FetchContent_MakeAvailable(GLEW)
	if (NOT TARGET GLEW::GLEW)
		add_library(GLEW::GLEW ALIAS GLEW)
	endif()
endif()

set(SDL2TTF_VENDORED ON CACHE BOOL "Use vendored FreeType" FORCE)
find_package(SDL2_ttf CONFIG QUIET)
if (NOT TARGET SDL2_ttf::SDL2_ttf)
	FetchContent_Declare(
		SDL2_ttf
		GIT_REPOSITORY https://github.com/libsdl-org/SDL_ttf.git
		GIT_TAG release-2.20.2
	)
	FetchContent_MakeAvailable(SDL2_ttf)
	if (NOT TARGET SDL2_ttf::SDL2_ttf)
		add_library(SDL2_ttf::SDL2_ttf ALIAS SDL2_ttf)
	endif()
endif()

# === Executable ===
add_executable(MyGame ${GAME_SOURCES})

# === Include Paths ===
target_include_directories(MyGame PRIVATE
	${CMAKE_SOURCE_DIR}/include
	${SDL2_INCLUDE_DIRS}
	${SDL2_IMAGE_INCLUDE_DIRS}
	${GLEW_INCLUDE_DIRS}
)

# === Link Libraries ===
target_link_libraries(MyGame PRIVATE
    SDL2::SDL2
	SDL2_image::SDL2_image
    GLEW::GLEW
	SDL2_ttf::SDL2_ttf
	freetype
    OpenGL::GL
)

# === Output Directories ===
set_target_properties(MyGame PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}
)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT MyGame)

