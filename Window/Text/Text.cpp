#include "Text.h"

Text::Text(const std::string& text, int x, int y, sf::Font* fontFamily, int fontSize) :
	text(text), x(x), y(y), fontFamily(fontFamily), fontSize(fontSize)
	{}
