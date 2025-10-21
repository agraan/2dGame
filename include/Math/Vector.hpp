#pragma once

namespace Math {

	class Vector2 {

		public :
			float x, y;

		public :

			Vector2(float x = 0, float y = 0) : x(x), y(y) {}

			inline Vector2 operator+(const Vector2& rhs) const { return {x + rhs.x, y + rhs.y}; }
			inline Vector2 operator-(const Vector2& rhs) const { return {x - rhs.x, y - rhs.y}; }
			inline Vector2 operator-() const { return {-x, -y}; }
			inline Vector2 operator*(float scalar) const { return {x * scalar, y * scalar}; }
			inline Vector2 operator/(float scalar) const { return {x / scalar, y / scalar}; }
			inline Vector2 operator*(const Vector2& rhs) const { return {x * rhs.x, y * rhs.y}; }
			inline Vector2 operator/(const Vector2& rhs) const { return {x / rhs.x, y / rhs.y}; }

			inline Vector2& operator=(const Vector2& rhs) { x = rhs.x; y = rhs.y; return *this; }
			inline Vector2& operator+=(const Vector2& rhs) { x += rhs.x; y += rhs.y; return *this; }
			inline Vector2& operator-=(const Vector2& rhs) { x -= rhs.x; y -= rhs.y; return *this; }
			inline Vector2& operator*=(const Vector2& rhs) { x *= rhs.x; y *= rhs.y; return *this; }
			inline Vector2& operator/=(const Vector2& rhs) { x /= rhs.x; y /= rhs.y; return *this; }
			inline Vector2& operator*=(float scalar) { x *= scalar; y *= scalar; return *this; }
			inline Vector2& operator/=(float scalar) { x /= scalar; y /= scalar; return *this; }

			inline bool    operator!=(const Vector2& rhs) const { return (x != rhs.x || y != rhs.y); }
			inline bool    operator==(const Vector2& rhs) const { return (x == rhs.x && y == rhs.y); }

			inline Vector2& Normalize() {
				float len = sqrt(x * x + y * y);
				if (len < 1e-8)
					return (*this = {0, 0});
				x /= len;
				y /= len;
				return *this;
			}
			inline Vector2 Normalized() const {
				float len = sqrt(x * x + y * y);
				if (len < 1e-8)
					return {0, 0};
				return {x / len, y / len};
			}
	};

	inline float Dot(const Vector2& a, const Vector2&b) { return (a.x * b.x + a.y * b.y); }
}
