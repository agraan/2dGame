#include "Sprite.hpp"

Sprite::Sprite(Texture* texture, int x, int y, int width, int height)
	: m_texture(texture),
	  m_width(width),
	  m_height(height) {
		m_srcRect = {0, 0, texture->GetWidth(), texture->GetHeight()};
		m_destRect = {x, y, width, height};
	}

void Sprite::Draw(Renderer& renderer) {
	SDL_RenderCopy(renderer.GetRenderer(), m_texture->GetTexture(),
			&m_srcRect, &m_destRect);
}

void Sprite::SetPosition(int x, int y) {
	m_destRect.x = x;
	m_destRect.y = y;
}

void Sprite::SetSize(int width, int height) {
	m_destRect.w = width;
	m_destRect.h = height;
	m_width = width;
	m_height = height;
}
