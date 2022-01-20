#pragma once
#include <cmath>

template<typename T>
class Vec2 {
public:
	class Vei2Hasher {
	public:

		std::size_t operator()(const Vec2<int> v) const {
			return ((std::hash<int>()(v.x)) ^ (std::hash<int>()(v.y)));
		}
	};

	Vec2()
		:
		x(0),
		y(0)
	{}

	Vec2(T _x, T _y) 
		:
		x(_x),
		y(_y)
	{}

	Vec2<T> operator+(const Vec2<T> other) const {
		
		return Vec2(x + other.x, y + other.y);
	}

	Vec2<T>& operator+=(const Vec2<T> other) {
		*this = *this + other;
		return *this;
	}

	Vec2<T> operator-(const Vec2<T> other) const {
		
		return Vec2(x - other.x, y - other.y);
	}
	Vec2<T> operator-() const {

		return Vec2(-x, -y);
	}

	Vec2<T>& operator-=(const Vec2<T> other) {
		*this = *this - other;
		return *this;
	}
	
	Vec2<T> operator*(const T other) const {
		return Vec2(x * other, y * other);
	}

	Vec2<T>& operator*=(const T other) {
		*this = *this * other;
		return *this;
	}

	Vec2<T> operator/(const T other) {
		return Vec2(x / other, y / other);
	}

	Vec2<T>& operator/=(const T other) {
		*this = *this / other;
		return *this;
	}

	bool operator==(const Vec2<T> other) const {
		return x == other.x && y == other.y;
	}

	bool operator!=(const Vec2<T> other) const {
		return !(*this == other);
	}

	T getLength() {
		return static_cast<T>(sqrt(x * x + y * y));
	}

	Vec2<T> normalize() {
		return { x / getLength(), y / getLength() };
	}
public:
	T x, y;
};