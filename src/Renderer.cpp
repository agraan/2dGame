#include "Renderer.hpp"

Renderer::Renderer(SDL_Window* window) {
	m_Renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (!m_Renderer) {
		std::cerr << "Failed to create renderer: " << SDL_GetError() << std::endl;
	}
}

Renderer::~Renderer() {
	if (m_Renderer)
		SDL_DestroyRenderer(m_Renderer);
}

Renderer& Renderer::operator=(const Renderer& src) {
	if (this != &src) {
		if (m_Renderer)
			SDL_DestroyRenderer(m_Renderer);
		m_Renderer = src.m_Renderer;
	}
	return *this;
}

void Renderer::Clear() {
	SDL_SetRenderDrawColor(m_Renderer, 0, 0, 0, 255);
	SDL_RenderClear(m_Renderer);
}

void Renderer::Present() {
	SDL_RenderPresent(m_Renderer);
}
