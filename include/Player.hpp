#pragma once

#include <string>
#include <map>
#include "Sprite.hpp"
#include "Texture.hpp"
#include "Entity.hpp"
#include "Pokemon.hpp"
#include "Math.hpp"

class Player : public Entity {

	public :

		Player() : Entity() {}
		using Entity::Entity;

		void HandleInput(const Uint8* keyState);
		bool CheckCollision(Pokemon poke);
};
