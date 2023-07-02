#pragma once
#include <string>
#include <vector>
#include <unordered_map>

#include "Camera.h"

#include "../Object/Object.h"
#include "Text/Text.h"

class Window {
private:
	int m_width = 0;
	int m_height = 0;


	Camera* m_camera = nullptr;
	sf::RenderWindow* m_window = nullptr;

	Window();
	void loadFont(const std::string& name, const std::string& filename);

	static Window& inst();

	std::vector<Object*> m_objects;
	std::vector<Text*> m_texts;

	std::vector<sf::Font> m_fonts;
	std::unordered_map<std::string, sf::Font*> m_fontsMap;
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

	static Text* createText(const std::string& text, int x, int y, const std::string& fontFamily, int fontSize);

	static Camera& camera();
	static int width();
	static int height();
	
	friend class Camera;
};
