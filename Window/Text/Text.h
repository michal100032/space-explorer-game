#pragma once

#include <SFML/Graphics.hpp>

#include <string>

struct Text {
	Text(const std::string& text, int x, int y, sf::Font* fontFamily, int fontSize);

	std::string text;
	int x, y;
	
	sf::Font* fontFamily;
	int fontSize;
};