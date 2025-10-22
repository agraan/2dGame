#pragma once

#include <SDL2/SDL_ttf.h>

struct GameConfig {
	int windowWidth;
	int windowHeight;
	TTF_Font* font;
	bool isFullscreen;
};

extern GameConfig g_GameConfig;
