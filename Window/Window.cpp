#include "Window.h"

#include <iostream>
#include <fstream>
#include <string>

#include "Time.h"

#include "../Object/CelestialBody.h"
#include "../Object/Spacecraft.h"

Window::Window() {
	
}

void Window::loadFont(const std::string& name, const std::string& filename) {
	sf::Font font;
	if (!font.loadFromFile(filename)) {
		std::cout << "Error: font " << name << " could not be loaded" << std::endl;
	} else {
		m_fonts.insert({ name, font });
	}
}

void Window::loadGameState() {
	std::ifstream file("saves/save.txt");
	
	std::vector<CelestialBody*> celestialBodies;
	std::vector<Spacecraft*> spacecraft;
	
	enum {
		SEC_CELESTIAL_BODIES = 0,
		SEC_SPACECRAFT = 1
	};
	int currentSection = -1;
	if (!file.good()) {
		file.close();
		file.open("saves/default.txt");
	}
	if (file.good()) {
		std::string line;
		while (std::getline(file, line)) {
			if (line[0] == ':') {
				currentSection = line == ":Celestial Bodies" ? SEC_CELESTIAL_BODIES : SEC_SPACECRAFT;
				if (currentSection == SEC_SPACECRAFT) {
					for (CelestialBody* body : celestialBodies) {
						body->calculateSoi();
					}
				}
			}
			else if (line.length() > 0 && line[0] != ' ') {
				if (currentSection == SEC_CELESTIAL_BODIES) {
					std::cout << "Celestial" << std::endl;
					
					std::string name = line;
					float mass, radius, orbitalRadius, initialAngle;
					uint32_t color;
					std::string parent;
					
					file >> mass >> radius >> color >> parent >> orbitalRadius >> initialAngle;
					CelestialBody* cb = createObject<CelestialBody>(name, mass, radius, sf::Color(color));

					celestialBodies.push_back(cb);
					if (parent != "ROOT") {
						for (CelestialBody* body : celestialBodies) {
							if (body->name() == parent) {
								body->addChild(cb, orbitalRadius, initialAngle);
								break;
							}
						}
					}
				}
				else if(currentSection == SEC_SPACECRAFT) {
					std::string name = line;
					std::string bodyName;
					CelestialBody* body = nullptr;
					float sma, ecc, tilt, ta, sam;
					file >> bodyName >> sma >> ecc >> tilt >> ta >> sam;
					for (CelestialBody* cb : celestialBodies) {
						if (cb->name() == bodyName) {
							body = cb;
							break;
						}
					}
					Orbit orbit(body, sma, ecc, tilt, ta, sam);
					Spacecraft* sc = createObject<Spacecraft>(name, orbit);
					spacecraft.push_back(sc);
				}
			}
		}
	}
	file.close();
}

void Window::saveGameState() {
	std::ofstream file("saves/save.txt");
	file << ":Celestial Bodies" << std::endl;
	for (Object* obj : inst().m_objects) {
		if (strcmp(typeid(*obj).name(), "class CelestialBody") == 0) {
			CelestialBody* body = (CelestialBody*)obj;
			file << body->name() << std::endl;
			file << body->mass() << ' ' << body->radius() << std::endl;
			file << body->colorInt() << std::endl;
			if (body->parent() == nullptr) {
				file << "ROOT" << std::endl << "0.0 0.0" << std::endl;
			} else {
				file << body->parent()->name() << std::endl << body->orbitalRadius() << ' ' << body->orbitalAngle() << std::endl;
			}
		}
	}
	file << ":Spacecraft" << std::endl;
	for (Object* obj : inst().m_objects) {
		if (strcmp(typeid(*obj).name(), "class Spacecraft") == 0) {
			Spacecraft* sc = (Spacecraft*)obj;
			Orbit* orbit = sc->getOrbit();
			file << sc->name() << std::endl;
			file << orbit->body()->name() << std::endl;
			file << orbit->semiMajorAxis() << ' ' << orbit->eccentricity() << ' ' << orbit->tilt() << ' ' << orbit->trueAnomaly() << ' ' << orbit->sam() << std::endl;
		}
	}

	file.close();
}

Window& Window::inst() {
	static Window window;
	return window;
}

void Window::init(const std::string& title, int width, int height) {
	inst().m_window = new sf::RenderWindow(sf::VideoMode(width, height), title);
	inst().m_window->setVerticalSyncEnabled(true);

	inst().m_width = width;
	inst().m_height = height;

	inst().m_camera = new Camera();

	inst().m_fonts.reserve(8);
	inst().loadFont("Consolas", "res/fonts/consola.ttf");

	inst().m_window->setKeyRepeatEnabled(false);

	Time::init();
	inst().loadGameState();

}

bool Window::isOpen() {
	return inst().m_window->isOpen();
}

void Window::handleEvents() {
	sf::Event event;
	while (inst().m_window->pollEvent(event))
	{
		switch (event.type) {
		case sf::Event::Closed:
			inst().m_window->close();
			break;
		case sf::Event::MouseWheelScrolled:
			if (event.mouseWheelScroll.delta > 0) {
				inst().m_camera->zoomIn();
			} else inst().m_camera->zoomOut();
			break;
		case sf::Event::KeyPressed:
			if (event.key.code == sf::Keyboard::Comma) {
				Time::setScale(Time::scale() / 2);
			} else if (event.key.code == sf::Keyboard::Period) {
				Time::setScale(Time::scale() * 2);
			} else if (event.key.code == sf::Keyboard::Slash) {
				Time::setScale(1.0f);
			}
			break;
		}
	}
}

void Window::updateObjects() {
	Time::setDelta(1.0f / 60);

	for (Object* object : inst().m_objects) {
		object->update();
	}
}

void Window::display() {
	inst().m_camera->render();
	
	for (sf::Text* text : inst().m_texts) {
		inst().m_window->draw(*text);
	}
	Window::inst().m_window->display();
}

void Window::close() {
	inst().saveGameState();

	for (Object* object : inst().m_objects) {
		delete object;
	}

	for (sf::Text* object : inst().m_texts) {
		delete object;
	}

	delete inst().m_window;
	delete inst().m_camera;
}

void Window::forEachObject(void(*func)(Object*)) {
	for (Object* obj : inst().m_objects) {
		func(obj);
	}
}

sf::Text* Window::createText(const std::string& text, float x, float y, const std::string& fontFamily, int fontSize, sf::Color color) {
	sf::Text* t = new sf::Text;
	t->setString(text);
	t->setCharacterSize(fontSize);
	t->setPosition(x, y);
	t->setFont(inst().m_fonts[fontFamily]);
	t->setFillColor(color);

	inst().m_texts.push_back(t);
	
	return t;
}

Camera& Window::camera() {
	return *inst().m_camera;
}

int Window::width() {
	return inst().m_width;
}

int Window::height() {
	return inst().m_height;
}
