#pragma once
#include <string>
#include <vector>
#include <unordered_map>

#include "Camera.h"

#include "../Object/Object.h"

class Window {
private:
	int m_width = 0;
	int m_height = 0;


	Camera* m_camera = nullptr;
	sf::RenderWindow* m_window = nullptr;

	Window();
	void loadFont(const std::string& name, const std::string& filename);
	void loadGameState();
	void saveGameState();

	static Window& inst();

	std::vector<Object*> m_objects;
	std::vector<sf::Text*> m_texts;

	std::unordered_map<std::string, sf::Font> m_fonts;
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

	template<typename T, typename... Args>
	static T* createInsertObject(Args... args) {
		T* object = new T(args...);
		inst().m_objects.insert(inst().m_objects.begin(), object);

		return object;
	}

	static sf::Text* createText(const std::string& text, float x, float y, const std::string& fontFamily, int fontSize, sf::Color color);

	static Camera& camera();
	static int width();
	static int height();
	
	friend class Camera;
};
