#pragma once

#include <SFML/Graphics.hpp>

#include <string>
#include <unordered_map>

class Fonts {
private:
	std::unordered_map<std::string, sf::Font> m_fonts;

	static Fonts& inst();
public:
	static sf::Font* get(const std::string& name);
	static void load(const std::string& name, const std::string& filename);
};