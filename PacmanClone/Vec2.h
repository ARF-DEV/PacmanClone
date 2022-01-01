#pragma once
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

	Vec2<T>& operator+(const Vec2<T> other) {
		this->x += other.x;
		this->y += other.y;
		return *this;
	}

	Vec2<T>& operator+=(const Vec2<T> other) {
		*this = *this + other;
		return *this;
	}

	Vec2<T>& operator-(const Vec2<T> other) {
		this->x -= other.x;
		this->y -= other.y;
		return *this;
	}

	Vec2<T>& operator-=(const Vec2<T> other) {
		*this = *this - other;
		return *this;
	}
	
	Vec2<T>& operator*(const Vec2<T> other) {
		this->x *= other.x;
		this->y *= other.y;
		return *this;
	}

	Vec2<T>& operator*=(const Vec2<T> other) {
		*this = *this * other;
		return *this;
	}

	T getX() {
		return x;
	}

	T getY() {
		return y;

	}
private:
	T x, y;
};