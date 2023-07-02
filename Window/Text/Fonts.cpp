#include "Fonts.h"

#include <iostream>

Fonts& Fonts::inst() {
	static Fonts fonts;
	return fonts;
}

sf::Font* Fonts::get(const std::string& name) {
	return &inst().m_fonts[name];
}

void Fonts::load(const std::string& name, const std::string& filename) {
	sf::Font font;
	if (!font.loadFromFile(filename)) {
		std::cout << "Error: font " << name << " could not be loaded" << std::endl;
	} else {
		inst().m_fonts.insert({ name, font });
	}
}
