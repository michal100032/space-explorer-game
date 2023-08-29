#include "Vector2f.h"

#include <cmath>

Vector2f::Vector2f(sf::Vector2f vector)
	: x(vector.x), y(vector.y) {}

Vector2f::Vector2f()
	: x(0.0f), y(0.0f) {}

Vector2f::Vector2f(float x, float y)
	: x(x), y(y) {}

float Vector2f::sqrMagnitude() const {
	return x * x + y * y;
}

float Vector2f::magnitude() const {
	return sqrtf(x * x + y * y);
}

Vector2f Vector2f::normalized() const {
	float mag = magnitude();
	return { x / mag, y / mag };
}

Vector2f Vector2f::operator+(const Vector2f& rhs) const {
	return { x + rhs.x, y + rhs.y };
}

Vector2f Vector2f::operator-(const Vector2f& rhs) const {
	return { x - rhs.x, y - rhs.y };
}

Vector2f Vector2f::operator*(float scalar) const {
	return { x * scalar, y * scalar };
}

Vector2f Vector2f::operator/(float scalar) const {
	return { x / scalar, y / scalar };
}

void Vector2f::operator+=(const Vector2f& rhs) {
	x += rhs.x; y += rhs.y;
}

void Vector2f::operator-=(const Vector2f& rhs) {
	x -= rhs.x; y -= rhs.y;
}

void Vector2f::operator*=(float scalar) {
	x *= scalar; y *= scalar;
}

void Vector2f::operator/=(float scalar) {
	x /= scalar; y /= scalar;
}

Vector2f Vector2f::operator-() const {
	return { -x, -y };
}

bool Vector2f::operator==(const Vector2f& rhs) const {
	return x == rhs.x && y == rhs.y;
}

Vector2f::operator sf::Vector2f() {
	return { x, y };
}

sf::Vector2f Vector2f::sf() const {
	return { x, y };
}

bool Vector2f::isZero() {
	return x == 0.0f && y == 0.0f;
}


float Vector2f::dot(const Vector2f& lhs, const Vector2f& rhs) {
	return lhs.x * rhs.x + lhs.y * rhs.y;
}

float Vector2f::distance(const Vector2f& lhs, const Vector2f& rhs) {
	return sqrtf((lhs.x - rhs.x) * (lhs.x - rhs.x) + (lhs.y - rhs.y) * (lhs.y - rhs.y));
}

float Vector2f::angle(const Vector2f& lhs, const Vector2f& rhs) {
	float a = lhs.x * rhs.y - lhs.y * rhs.x;
	return (a > 0 ? 1 : -1) * acosf(dot(lhs, rhs) / lhs.magnitude() / rhs.magnitude());
}

std::ostream& operator<<(std::ostream& os, const Vector2f& vec) {
	return os << "(" << vec.x << ", " << vec.y << ")";
}