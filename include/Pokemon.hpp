#pragma once

#include <string>
#include <map>
#include "Sprite.hpp"
#include "Texture.hpp"
#include "Entity.hpp"
#include <random>
#include "Math.hpp"

class Pokemon : public Entity {

	private :

		Math::Vector2 m_Acceleration = {100.0f, 100.0f};

	public :
		Pokemon(std::map<std::string, Texture*>& textures,
		        const Math::Vector2& position = Math::Vector2(0.0f, 0.0f));
		~Pokemon() = default;

		void RandomizeDirection(float minAngle = 0.0f, float maxAngle = 360.0f);

		Math::Vector2 GetAcceleration() const { return m_Acceleration; }
		void SetAcceleration(const Math::Vector2& acceleration) { m_Acceleration = acceleration; }

};
