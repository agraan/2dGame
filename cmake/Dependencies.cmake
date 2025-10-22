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
endif()


find_package(SDL2_image CONFIG QUIET)
if (NOT TARGET SDL2_image::SDL2_image)

	FetchContent_Declare(
		SDL2_image
		GIT_REPOSITORY https://github.com/libsdl-org/SDL_image.git
		GIT_TAG release-2.8.2
	)
	FetchContent_MakeAvailable(SDL2_image)
endif()

find_package(GLEW REQUIRED)
if (NOT TARGET GLEW::GLEW)
	FetchContent_Declare(
		GLEW
		GIT_REPOSITORY https://github.com/nigels-com/glew.git
		GIT_TAG glew-2.2.0
	)
	FetchContent_MakeAvailable(GLEW)
endif()
