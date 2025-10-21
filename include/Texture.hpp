#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <iostream>
#include <filesystem>
#include "Renderer.hpp"
#include "Globals.hpp"

class Texture {

	private :

		SDL_Texture* m_Texture = nullptr;
		int m_Width = 0;
		int m_Height = 0;

	public :

		Texture(Renderer* renderer, const std::filesystem::path& filePath);
		~Texture();

		SDL_Texture* GetTexture() const { return m_Texture; }
		int GetWidth() const { return m_Width; }
		int GetHeight() const { return m_Height; }

};
