#include "GameTimer.hpp"

void GameTimer::Start() {
	m_StartTicks = SDL_GetTicks64();
	m_IsRunning = true;
}

void GameTimer::Stop() {
	m_IsRunning = false;
}

float GameTimer::GetElapsedSeconds() const {
	if (!m_IsRunning) return 0.0f;
	Uint64 current = SDL_GetTicks64();
	return (current - m_StartTicks) / 1000.0f;
}

void GameTimer::UpdateTimerTexture(SDL_Renderer* renderer, TTF_Font* font, const std::string& text) {
	if (text == m_TimerText)
		return;
	if (m_TimerTexture) {
		SDL_DestroyTexture(m_TimerTexture);
		m_TimerTexture = nullptr;
	}

	SDL_Color color = {255, 255, 255, 255};
	SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
	m_TimerTexture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_Rect dstRect = { m_TimerWidth, m_TimerHeight, surface->w, surface->h };
	SDL_RenderCopy(renderer, m_TimerTexture, NULL, &dstRect);

	SDL_FreeSurface(surface);
}
