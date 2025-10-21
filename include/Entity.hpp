
#pragma once

#include <string>
#include <map>
#include "Sprite.hpp"
#include "Texture.hpp"
#include "Math.hpp"

class Entity {

	protected :

		std::map<std::string, Texture*> m_Textures;
		Math::Vector2 m_Position;
		Math::Vector2 m_Direction;
		Sprite* m_Sprite = nullptr;

	public :

		Entity() = default;
		Entity(std::map<std::string, Texture*>& textures,
		       const Math::Vector2& position = Math::Vector2(0.0f, 0.0f),
		       const Math::Vector2& direction = Math::Vector2(1.0f, 1.0f));
		virtual ~Entity();

		void SetSprite(const std::string& textureKey, int width, int height);

		const Math::Vector2& GetPosition() const;
		const Math::Vector2& GetDirection() const;

		Sprite* GetSprite() const;

		void SetPosition(const Math::Vector2& position);
		void SetDirection(const Math::Vector2& direction);
		void Move(const Math::Vector2& delta);
		void Update(Renderer& renderer);
		virtual void HandleInput(const Uint8* keyState);
};
