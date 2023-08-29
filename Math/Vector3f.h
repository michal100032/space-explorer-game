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

	float sqrMagnitude() const;
	float magnitude() const;
	Vector3f normalized() const;

	Vector3f operator +(const Vector3f& rhs);
	Vector3f operator -(const Vector3f& rhs);
	Vector3f operator *(float scalar);
	Vector3f operator /(float scalar);


	Vector3f operator -();

	void operator +=(const Vector3f& rhs);
	void operator -=(const Vector3f& rhs);
	void operator *=(float scalar);
	void operator /=(float scalar);

	bool operator ==(const Vector3f& rhs);
	
	operator sf::Vector3f();
	sf::Vector3f sf();
	sf::Vector2f sf2();

	operator Vector2f();


	static float dot(const Vector3f& lhs, const Vector3f& rhs);
	static Vector3f cross(const Vector3f& lhs, const Vector3f rhs);
	static Vector3f cross(const Vector2f& lhs, const Vector2f rhs);

	static float distance(const Vector3f& lhs, const Vector3f& rhs);

};

std::ostream& operator<<(std::ostream& os, const Vector3f& vec);