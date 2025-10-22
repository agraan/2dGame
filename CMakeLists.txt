cmake_minimum_required(VERSION 3.22)
project(MyGame LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

# ============================================================
# 🔹 SDL2
# ============================================================
FetchContent_Declare(
  SDL2
  GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
  GIT_TAG        release-2.30.2
)
FetchContent_MakeAvailable(SDL2)

# ============================================================
# 🔹 SDL2_ttf (with vendored FreeType)
# ============================================================
set(SDL2TTF_VENDORED ON CACHE BOOL "" FORCE)
FetchContent_Declare(
  SDL2_ttf
  GIT_REPOSITORY https://github.com/libsdl-org/SDL_ttf.git
  GIT_TAG        release-2.22.0
)
FetchContent_MakeAvailable(SDL2_ttf)

# ============================================================
# 🔹 SDL2_image (with vendored PNG/JPG/WebP)
# ============================================================
set(SDL2IMAGE_VENDORED ON CACHE BOOL "" FORCE)
FetchContent_Declare(
  SDL2_image
  GIT_REPOSITORY https://github.com/libsdl-org/SDL_image.git
  GIT_TAG        release-2.8.2
)
FetchContent_MakeAvailable(SDL2_image)

# ============================================================
# 🔹 GLEW (Perlmint CMake fork)
# ============================================================
set(BUILD_UTILS OFF CACHE BOOL "" FORCE)
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
  glew
  GIT_REPOSITORY https://github.com/Perlmint/glew-cmake.git
  GIT_TAG        origin/master
)
FetchContent_GetProperties(glew)
if(NOT glew_POPULATED)
  FetchContent_Populate(glew)
  add_subdirectory(${glew_SOURCE_DIR} ${glew_BINARY_DIR})
endif()

# ============================================================
# 🔹 OpenGL (system library)
# ============================================================
find_package(OpenGL REQUIRED)

# ============================================================
# 🔹 Game executable
# ============================================================
file(GLOB_RECURSE GAME_SOURCES CONFIGURE_DEPENDS
    src/*.cpp
)

add_executable(MyGame ${GAME_SOURCES})

# ============================================================
# 🔹 Include dirs (optional)
# ============================================================
target_include_directories(MyGame PRIVATE
	${PROJECT_SOURCE_DIR}/include
  ${SDL2_INCLUDE_DIRS}
  ${SDL2_TTF_INCLUDE_DIRS}
  ${SDL2_IMAGE_INCLUDE_DIRS}
)

# ============================================================
# 🔹 Link all libraries
# ============================================================
target_link_libraries(MyGame PRIVATE
  SDL2::SDL2
  SDL2_ttf::SDL2_ttf
  SDL2_image::SDL2_image
  libglew_static
  OpenGL::GL            # ✅ official OpenGL target
)

# ============================================================
# 🔹 Platform specifics
# ============================================================
if(WIN32)
  add_definitions(-D_CRT_SECURE_NO_WARNINGS)
elseif(APPLE)
  find_library(COCOA_LIBRARY Cocoa)
  target_link_libraries(MyGame PRIVATE ${COCOA_LIBRARY})
elseif(UNIX AND NOT APPLE)
  target_link_libraries(MyGame PRIVATE pthread dl)
endif()

# ============================================================
# 🔹 Output folder
# ============================================================
set_target_properties(MyGame PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../
)

