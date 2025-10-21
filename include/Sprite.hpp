#pragma once
#include "Texture.hpp"
#include "Renderer.hpp"

class Sprite {

	private:
		Texture* m_texture;
		int m_width;
		int m_height;
		SDL_Rect m_srcRect;
		SDL_Rect m_destRect;

	public:

		Sprite(Texture* texture, int x, int y, int width, int height);
		~Sprite() = default;

		int GetWidth() const { return m_width; }
		int GetHeight() const { return m_height; }

		void Draw(Renderer& renderer);
		void SetPosition(int x, int y);
		void SetSize(int width, int height);

};
