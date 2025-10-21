#include "Entity.hpp"

Entity::Entity(std::map<std::string, Texture*>& textures, const Math::Vector2& position,
		const Math::Vector2& direction)
	: m_Textures(textures),
      m_Position(position),
	  m_Direction(direction.Normalized()) {}

Entity::~Entity() {}

void Entity::SetSprite(const std::string& textureKey, int width, int height) {
	if (m_Textures.find(textureKey) != m_Textures.end()) {
		m_Sprite = new Sprite(m_Textures[textureKey], m_Position.x, m_Position.y, width, height);
	}
}

const Math::Vector2& Entity::GetPosition() const { return m_Position; }

const Math::Vector2& Entity::GetDirection() const { return m_Direction; }

Sprite* Entity::GetSprite() const { return m_Sprite; }

void Entity::SetPosition(const Math::Vector2& position) {
	m_Position = position;
}

void Entity::SetDirection(const Math::Vector2& Direction) {
	m_Direction = Direction;
}

void Entity::Move(const Math::Vector2& delta) { m_Position += delta * m_Direction; }

void Entity::Update(Renderer& renderer) {
	m_Sprite->SetPosition(static_cast<int>(m_Position.x), static_cast<int>(m_Position.y));
	m_Sprite->Draw(renderer);
}

void Entity::HandleInput(const Uint8* keyState) {
	// Default implementation does nothing
}
