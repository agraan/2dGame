#pragma once

#include <SDL2/SDL.h>

class Time {

	private :

		static Uint64 m_LastCounter;
		static float m_DeltaTime;

	public :

		static void Update();
		static float DeltaTime() { return m_DeltaTime; }

};
