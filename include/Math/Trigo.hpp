#pragma once
#include <cmath>
namespace Math {

	constexpr float PI = 3.14159265358979323846f;
	constexpr float TWO_PI = 2.0f * PI;
	constexpr float RAD_TO_DEG = 180.0f / PI;
	constexpr float DEG_TO_RAD = PI / 180.0f;

	inline float Radian(float degrees) {
		return degrees * DEG_TO_RAD;
	}

	inline float Degrees(float radians) {
		return radians * RAD_TO_DEG;
	}

	inline float Sin(float degrees) {
		return sinf(Radian(degrees));
	}
	inline float Cos(float degrees) {
		return cosf(Radian(degrees));
	}

}
