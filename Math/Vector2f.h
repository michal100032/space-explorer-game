#pragma once

#include <SFML/System/Vector2.hpp>
#include <ostream>

struct Vector2f {
public:
	float x, y;
	
	Vector2f();
	Vector2f(float x, float y);
	Vector2f(sf::Vector2f vector);

	float sqrMagnitude() const;
	float magnitude() const;
	Vector2f normalized() const;

	Vector2f operator +(const Vector2f& rhs) const;
	Vector2f operator -(const Vector2f& rhs) const;
	Vector2f operator *(float scalar) const;
	Vector2f operator /(float scalar) const;

	void operator +=(const Vector2f& rhs);
	void operator -=(const Vector2f& rhs);
	void operator *=(float scalar);
	void operator /=(float scalar);


	Vector2f operator -() const;

	bool operator ==(const Vector2f& rhs) const;
	
	operator sf::Vector2f();
	sf::Vector2f sf() const;

	bool isZero();

	static float dot(const Vector2f& lhs, const Vector2f& rhs);
	static float distance(const Vector2f& lhs, const Vector2f& rhs);
	static float angle(const Vector2f& lhs, const Vector2f& rhs);
};

std::ostream& operator<<(std::ostream& os, const Vector2f& vec);