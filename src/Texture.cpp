#include "Texture.hpp"

Texture::Texture(Renderer* renderer, const std::filesystem::path& filePath) {
	IMG_Init(IMG_INIT_PNG);
	m_Texture = IMG_LoadTexture(renderer->GetRenderer(), filePath.string().c_str());
	if (!m_Texture) {
		std::cerr << "Failed to load texture at " << filePath
				  << " : " << IMG_GetError() << std::endl;
	}
	SDL_QueryTexture(m_Texture, nullptr, nullptr, &m_Width, &m_Height);
}

Texture::~Texture() {
	if (m_Texture)
		SDL_DestroyTexture(m_Texture);
}
