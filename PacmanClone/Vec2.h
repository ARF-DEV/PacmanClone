#pragma once
#include <cmath>
template<typename T>
class Vec2 {
public:
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

	Vec2<T> operator+(const Vec2<T> other) {
		
		return Vec2(x + other.x, y + other.y);
	}

	Vec2<T>& operator+=(const Vec2<T> other) {
		*this = *this + other;
		return *this;
	}

	Vec2<T> operator-(const Vec2<T> other) {
		
		return Vec2(x - other.x, y - other.y);
	}
	Vec2<T> operator-() {

		return Vec2(-x, -y);
	}

	Vec2<T>& operator-=(const Vec2<T> other) {
		*this = *this - other;
		return *this;
	}
	
	Vec2<T> operator*(const T other) {
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

	bool operator==(const Vec2<T> other) {
		return x == other.x && y == other.y;
	}

	bool operator!=(const Vec2<T> other) {
		return !(*this == other);
	}

	T getLength() {
		return static_cast<T>(sqrt(x * x + y * y));
	}
public:
	T x, y;
};