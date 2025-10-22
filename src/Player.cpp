#include "Player.hpp"

#include "Player.hpp"

void Player::HandleInput(const Uint8* keyState, float dt) {
	Math::Vector2 movement(0, 0);

	if (keyState[SDL_SCANCODE_W]) { movement.y -= 1; }
	if (keyState[SDL_SCANCODE_S]) { movement.y += 1; }
	if (keyState[SDL_SCANCODE_A]) { movement.x -= 1; }
	if (keyState[SDL_SCANCODE_D]) { movement.x += 1; }

	if (movement.x != 0 || movement.y != 0) {
		movement.Normalize();
	}
	m_Direction = movement;
	Move(Math::Vector2(400.0f, 400.0f), dt);
}

bool Player::CheckCollision(Pokemon poke) {
	Math::Vector2 poke_pos = poke.GetPosition();
	Sprite* poke_sprite = poke.GetSprite();
	if ((m_Position.x >= poke_pos.x) && (m_Position.x <= (poke_pos.x + poke_sprite->GetWidth()))) {
		if ((m_Position.y >= poke_pos.y) && (m_Position.y <= (poke_pos.y + poke_sprite->GetHeight()))) {
			return true;
		}
	}
	return false;
}
