#include "Pokemon.hpp"

Pokemon::Pokemon(std::map<std::string, Texture*>& textures,
		const Math::Vector2& position)
	: Entity(textures, position) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> distrib(-1.0, 1.0);
	Math::Vector2 dir = Math::Vector2(distrib(gen), distrib(gen));
	dir.Normalize();
	SetDirection(dir);
}

void Pokemon::RandomizeDirection(float minAngle, float maxAngle) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> distrib(Math::Cos(minAngle), Math::Sin(maxAngle));
	Math::Vector2 dir = Math::Vector2(distrib(gen), distrib(gen));
	dir.Normalize();
	SetDirection(dir);
}
