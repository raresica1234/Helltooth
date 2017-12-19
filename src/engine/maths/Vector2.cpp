#include "Vector2.hpp"

namespace ht { namespace maths {

	Vector2::Vector2(): x(0), y(0) {}
	Vector2::Vector2(float x, float y) : x(x), y(y) {}

	Vector2 operator+(Vector2 left, const Vector2& right) {
		left.x += right.x;
		left.y += right.y;
		return left;
	}

	Vector2 operator-(Vector2 left, const Vector2& right) {
		left.x -= right.x;
		left.y -= right.y;
		return left;
	}

	Vector2 operator*(Vector2 left, const Vector2& right) {
		left.x *= right.x;
		left.y *= right.y;
		return left;
	}

	Vector2 operator/(Vector2 left, const Vector2& right) {
		left.x /= right.x;
		left.y /= right.y;
		return left;
	}

	void Vector2::operator+=(const Vector2& other) {
		x += other.x;
		y += other.y;
	}

	void Vector2::operator-=(const Vector2& other) {
		x -= other.x;
		y -= other.y;
	}

	void Vector2::operator*=(const Vector2& other) {
		x *= other.x;
		y *= other.y;
	}

	void Vector2::operator/=(const Vector2& other) {
		x /= other.x;
		y /= other.y;
	}

	Vector2 operator+(Vector2 left, float right) {
		left.x += right;
		left.y += right;
		return left;
	}

	Vector2 operator-(Vector2 left, float right) {
		left.x -= right;
		left.y -= right;
		return left;
	}

	Vector2 operator*(Vector2 left, float right) {
		left.x *= right;
		left.y *= right;
		return left;
	}

	Vector2 operator/(Vector2 left, float right) {
		left.x /= right;
		left.y /= right;
		return left;
	}

	void Vector2::operator+=(float other) {
		x += other;
		y += other;
	}

	void Vector2::operator-=(float other) {
		x -= other;
		y -= other;
	}

	void Vector2::operator*=(float other) {
		x *= other;
		y *= other;
	}

	void Vector2::operator/=(float other) {
		x /= other;
		y /= other;
	}

} }