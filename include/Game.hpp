#pragma once

#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <iostream>
#include <filesystem>
#include <vector>
#include <string>
#include <map>
#include <random>
#include <SDL2/SDL_ttf.h>

#include "Globals.hpp"
#include "Renderer.hpp"
#include "Texture.hpp"
#include "Sprite.hpp"
#include "Player.hpp"
#include "Pokemon.hpp"
#include "GameTimer.hpp"
#include "Time.hpp"
#include "Math.hpp"

class Game {

	private :

		bool m_isRunning = true;

		SDL_Window* m_window = nullptr;
		SDL_GLContext m_glContext = nullptr;
		Renderer* m_Renderer = nullptr;
		GameTimer m_Timer;
		Time m_DeltaTime;
		Player m_Player;
		std::vector<Pokemon> m_Pokemons;
		std::map<std::string, Texture*> m_Textures;
		std::map<std::string, Sprite*> m_Sprites;

	public :

		Game() = default;
		~Game() = default;

		int Init(void);
		void Run(void);
		void Shutdown(void);

	private :

		void ProcessEvents(void);
		void LoadAssets(void);
		void LoadAllTexturesFromDir(const std::string& directoryPath);
		void AddPokemon(Math::Vector2 position, const std::string& textureKey, int width, int height);
		void Render(void);
		void MovePokemon(float dt);
		bool CheckCollisions(void);

};
