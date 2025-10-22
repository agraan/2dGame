#pragma once

#include <SDL2/SDL.h>
#include <string>
#include <iomanip>
#include <sstream>
#include <SDL2/SDL_ttf.h>
#include "Globals.hpp"

class GameTimer {
	private:

		Uint64 m_StartTicks = 0;
		bool m_IsRunning = false;
		SDL_Texture* m_TimerTexture = nullptr;
		std::string m_TimerText = "";
		int m_TimerWidth = g_GameConfig.windowWidth / 2 - 50;
		int m_TimerHeight = 10;

	public:

		void Start();
		void Stop();
		float GetElapsedSeconds() const;
		void UpdateTimerTexture(SDL_Renderer* renderer, TTF_Font* font, const std::string& text);
};

inline std::string FormatTime(float seconds) {
	int totalSeconds = static_cast<int>(seconds);
	int minutes = totalSeconds / 60;
	int secs = totalSeconds % 60;

	std::ostringstream ss;
	ss << std::setw(2) << std::setfill('0') << minutes
	   << ":"
	   << std::setw(2) << std::setfill('0') << secs;
	return ss.str();
}

inline void RenderText(SDL_Renderer* renderer, TTF_Font* font, const std::string& text, int x, int y) {
    SDL_Color color = {255, 255, 255, 255};
    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_Rect dstRect = { x, y, surface->w, surface->h };
	SDL_RenderCopy(renderer, texture, NULL, &dstRect);

	SDL_FreeSurface(surface);
	SDL_DestroyTexture(texture);
}
