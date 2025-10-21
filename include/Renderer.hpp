#pragma once
#include <SDL2/SDL.h>
#include <string>
#include <iostream>
#include "Globals.hpp"


class Renderer {

	private :

		SDL_Renderer* m_Renderer = nullptr;

	public :

		Renderer(SDL_Window* window);
		~Renderer();

		Renderer& operator=(const Renderer&);

		SDL_Renderer* GetRenderer() const { return m_Renderer; }

		void Present();
		void Clear();

};
