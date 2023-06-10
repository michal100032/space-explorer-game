#pragma once

#include <SFML/Graphics.hpp>
#include <string>

#include "../Math/Vector2f.h"

class Object {
protected:
	Vector2f m_position;
	float m_rotation;

	std::string m_name;

	bool m_preserveScreenSize = false;
protected:
	Object(const std::string& name);
public:

	virtual void update() {}

	virtual Vector2f getPosition();
	virtual void setPosition(float x, float y);
	virtual void move(float x, float y);

	virtual float getRotation();
	virtual void setRotation(float rotation);
	virtual void rotate(float angle);

	virtual Vector2f getVelocity() {
		return { 0.0f, 0.0f };
	}
	virtual sf::Shape* getShape() { return nullptr; }

	virtual const std::string& getName();
	virtual void setName(const std::string& name);

	bool preserveScreenSize();
};