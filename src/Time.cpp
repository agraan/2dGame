#include "Time.hpp"

Uint64 Time::m_LastCounter = 0;
float Time::m_DeltaTime = 0.0f;

void Time::Update() {
	Uint64 current = SDL_GetPerformanceCounter();
	if (m_LastCounter == 0) {
		m_LastCounter = current;
		m_DeltaTime = 0.0f;
		return ;
	}
	Uint64 freq = SDL_GetPerformanceFrequency();
	m_DeltaTime = 0.0f;
}
