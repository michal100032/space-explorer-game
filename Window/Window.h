#pragma once
#include <string>
#include <vector>

#include "Camera.h"
#include "../Object/Object.h"

class Window {
private:
	int m_width = 0;
	int m_height = 0;


	Camera* m_camera = nullptr;
	sf::RenderWindow* m_window = nullptr;

	Window();

	static Window& inst();

	std::vector<Object*> m_objects;

public:
	static void init(const std::string& title, int width, int height);
	static bool isOpen();
	static void handleEvents();
	static void updateObjects();
	static void display();
	static void close();

	static void forEachObject(void (*func)(Object*));

	template<typename T, typename... Args>
	static T* createObject(Args... args) {
		T* object = new T(args...);
		inst().m_objects.push_back(object);
		
		return object;
	}

	static Camera& camera();
	static int width();
	static int height();

	friend class Camera;
};
