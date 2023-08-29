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
	bool m_active = true;
protected:
	Object(const std::string& name);
	Object(const std::string& name, const Vector2f& position);
	Object(const std::string& name, const Vector2f& position, float rotation);
public:
	const std::string& name() const;
	virtual void update() {}

	virtual Vector2f getPosition();
	virtual void setPosition(float x, float y);
	virtual void setPosition(const Vector2f& position);

	virtual void move(float x, float y);

	virtual float getRotation();
	virtual void setRotation(float rotation);
	virtual void rotate(float angle);

	virtual Vector2f getVelocity() {
		return { 0.0f, 0.0f };
	}
	virtual sf::Drawable* getDrawable() { return nullptr; }

	virtual void setName(const std::string& name);

	bool preserveScreenSize();
	bool isActive();
	void setActive(bool active);
};