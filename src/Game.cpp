#include "Game.hpp"

int Game::Init(void) {
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		std::cerr << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
		return (-1);
	}

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	if (TTF_Init() == -1) {
		std::cerr << "Failed to initialize SDL_ttf: " << TTF_GetError() << std::endl;
		SDL_Quit();
		return (-1);
	}

	g_GameConfig.font = TTF_OpenFont("assets/fonts/timer-font.ttf", 24);

	m_window = SDL_CreateWindow("MyGame", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			g_GameConfig.windowWidth, g_GameConfig.windowHeight, SDL_WINDOW_OPENGL);
	if (!m_window) {
		std::cerr << "Failed to create SDL window: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return (-1);
	}

	m_glContext = SDL_GL_CreateContext(m_window);

	if (glewInit() != GLEW_OK) {
		std::cerr << "Failed to initialize GLEW" << std::endl;
		SDL_DestroyWindow(m_window);
		SDL_Quit();
		return (-1);
	}

	glViewport(0, 0, g_GameConfig.windowWidth, g_GameConfig.windowHeight);
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

	LoadAssets();
	return (1);
}

void Game::Run() {
	m_Timer.Start();
	while (m_isRunning) {
		m_DeltaTime.Tick();
		float dt = Time::GetDeltaTime();
		ProcessEvents();
		glClear(GL_COLOR_BUFFER_BIT);
		MovePokemon(dt);
		const Uint8 *state = SDL_GetKeyboardState(NULL);
		m_Player.HandleInput(state, dt);
		if (CheckCollisions() == true)
			m_isRunning = false;
		if (m_Renderer) {
			Render();
		}
		m_Timer.UpdateTimerTexture(m_Renderer->GetRenderer(), g_GameConfig.font,
			FormatTime(m_Timer.GetElapsedSeconds()));
		m_Renderer->Present();
		SDL_GL_SwapWindow(m_window);
	}
}

void Game::Shutdown() {
	delete m_Renderer;
	for (auto& texPair : m_Textures) {
		delete texPair.second;
	}
	TTF_CloseFont(g_GameConfig.font);
	TTF_Quit();
	SDL_GL_DeleteContext(m_glContext);
	SDL_DestroyWindow(m_window);
	SDL_Quit();
}

void Game::ProcessEvents() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			m_isRunning = false;
		}

	}
}

void Game::LoadAllTexturesFromDir(const std::string& directoryPath) {
	for (const auto& file : std::filesystem::directory_iterator(directoryPath)) {
		if (file.is_regular_file() && file.path().extension() == ".png") {
			std::string key = file.path().stem().string();
			m_Textures[key] = new Texture(m_Renderer, file.path());
		}
	}
}

void Game::AddPokemon(Math::Vector2 position, const std::string& textureKey, int width, int height) {
	Pokemon pok(m_Textures, position);
	pok.SetSprite(textureKey, width, height);
	m_Pokemons.push_back(pok);
}

void Game::LoadAssets() {
	m_Renderer = new Renderer(m_window);
	LoadAllTexturesFromDir("assets/textures/");

	AddPokemon(Math::Vector2(200, 200), "charizard", 120, 120);
	AddPokemon(Math::Vector2(400, 200), "tortipouss", 100, 100);
	AddPokemon(Math::Vector2(600, 200), "giratina", 120, 120);
	AddPokemon(Math::Vector2(800, 200), "mammochon", 160, 140);
	AddPokemon(Math::Vector2(1000, 200), "chapignon", 160, 160);

	m_Player = Player(m_Textures, Math::Vector2(800, 800));
	m_Player.SetSprite("thomas-bizarre", 80, 80);
}

void Game::Render() {
	m_Renderer->Clear();
	for (auto& poke : m_Pokemons) {
		poke.Update(*m_Renderer);
	}
	m_Player.Update(*m_Renderer);
}

void Game::MovePokemon(float dt) {
	for (auto& poke : m_Pokemons) {
		Math::Vector2 oldDir = poke.GetDirection();
		Math::Vector2 pos = poke.GetPosition();
		if (pos.x < 0)
			poke.RandomizeDirection(-90.0f, 90.0f);
		else if (pos.x > g_GameConfig.windowWidth - poke.GetSprite()->GetWidth())
			poke.RandomizeDirection(90.0f, 270.0f);
		if (pos.y < 0)
			poke.RandomizeDirection(0.0f, 180.0f);
		else if (pos.y > g_GameConfig.windowHeight - poke.GetSprite()->GetHeight())
			poke.RandomizeDirection(180.0f, 360.0f);
		if (oldDir != poke.GetDirection())
			poke.SetAcceleration((poke.GetAcceleration() + Math::Vector2(20.0f, 20.0f)));
		poke.Move(poke.GetAcceleration(), dt);
	}
}

bool Game::CheckCollisions() {
	for (auto& poke : m_Pokemons) {
		if (m_Player.CheckCollision(poke)) {
			return (true);
		}
	}
	return (false);
}
