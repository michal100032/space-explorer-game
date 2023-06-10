#pragma once

#include <SFML/System/Vector3.hpp>
#include <ostream>

#include "Vector2f.h"

struct Vector3f {
public:
	float x, y, z;
	
	Vector3f();
	Vector3f(float x, float y, float z);
	Vector3f(Vector2f vector);
	Vector3f(sf::Vector3f vector);

	float sqrMagnitude();
	float magnitude();
	Vector3f normalized();

	Vector3f operator +(const Vector3f& rhs);
	Vector3f operator -(const Vector3f& rhs);
	Vector3f operator *(float scalar);
	Vector3f operator /(float scalar);

	void operator +=(const Vector3f& rhs);
	void operator -=(const Vector3f& rhs);
	void operator *=(float scalar);
	void operator /=(float scalar);

	bool operator ==(const Vector3f& rhs);
	
	operator sf::Vector3f();
	sf::Vector3f sf();


	static float dot(const Vector3f& lhs, const Vector3f& rhs);
	static Vector3f cross(const Vector3f& lhs, const Vector3f rhs);
	static Vector3f cross(const Vector2f& lhs, const Vector2f rhs);

	static float distance(const Vector3f& lhs, const Vector3f& rhs);

};

std::ostream& operator<<(std::ostream& os, const Vector3f& vec);