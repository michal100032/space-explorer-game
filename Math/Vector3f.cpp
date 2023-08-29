#include "Vector3f.h"

#include <cmath>

Vector3f::Vector3f(sf::Vector3f vector)
	: x(vector.x), y(vector.y), z(vector.z) {}

Vector3f::Vector3f()
	: x(0.0f), y(0.0f), z(0.0f) {}

Vector3f::Vector3f(float x, float y, float z)
	: x(x), y(y), z(z) {}

Vector3f::Vector3f(Vector2f vector) 
	: x(vector.x), y(vector.y), z(0.0f) {}

float Vector3f::sqrMagnitude() const {
	return x * x + y * y + z * z;
}

float Vector3f::magnitude() const {
	return sqrtf(x * x + y * y + z * z);
}

Vector3f Vector3f::normalized() const {
	float mag = magnitude();
	return { x / mag, y / mag, z / mag };
}

Vector3f Vector3f::operator+(const Vector3f& rhs) {
	return { x + rhs.x, y + rhs.y, z + rhs.z };
}

Vector3f Vector3f::operator-(const Vector3f& rhs) {
	return { x - rhs.x, y - rhs.y, z - rhs.z };
}

Vector3f Vector3f::operator*(float scalar) {
	return { x * scalar, y * scalar, z * scalar };
}

Vector3f Vector3f::operator/(float scalar) {
	return { x / scalar, y / scalar, z / scalar };
}

Vector3f Vector3f::operator-() {
	return { -x, -y, -z };
}

void Vector3f::operator+=(const Vector3f& rhs) {
	x += rhs.x; y += rhs.y; z += rhs.z;
}

void Vector3f::operator-=(const Vector3f& rhs) {
	x -= rhs.x; y -= rhs.y; z -= rhs.z;
}

void Vector3f::operator*=(float scalar) {
	x *= scalar; y *= scalar; z *= scalar;
}

void Vector3f::operator/=(float scalar) {
	x /= scalar; y /= scalar; z /= scalar;
}

bool Vector3f::operator==(const Vector3f& rhs) {
	return x == rhs.x && y == rhs.y && z == rhs.z;
}

Vector3f::operator sf::Vector3f() {
	return { x, y, z };
}

sf::Vector3f Vector3f::sf() {
	return { x, y, z };
}

sf::Vector2f Vector3f::sf2() {
	return { x, y };
}

Vector3f::operator Vector2f() {
	return { x, y };
}


float Vector3f::dot(const Vector3f& lhs, const Vector3f& rhs) {
	return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
}

Vector3f Vector3f::cross(const Vector3f& lhs, const Vector3f rhs) {
	return {
		lhs.y * rhs.z - lhs.z * rhs.y,
		lhs.z * rhs.x - lhs.x * rhs.z,
		lhs.x * rhs.y - lhs.y * rhs.x
	};
}

Vector3f Vector3f::cross(const Vector2f& lhs, const Vector2f rhs) {
	return { 0.0f, 0.0f, lhs.x * rhs.y - lhs.y * rhs.x };
}

float Vector3f::distance(const Vector3f& lhs, const Vector3f& rhs) {
	return sqrtf(
		(lhs.x - rhs.x) * (lhs.x - rhs.x) + 
		(lhs.y - rhs.y) * (lhs.y - rhs.y) +
		(lhs.z - rhs.z) * (lhs.z - rhs.z)
	);
}

std::ostream& operator<<(std::ostream& os, const Vector3f& vec) {
	return os << "(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
}