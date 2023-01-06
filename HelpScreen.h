#pragma once
#include "SFML/Graphics.hpp"
#define MAX_NUMBER_OF_SLOTS 5
class HelpScreen
{
private:
	sf::Text text[MAX_NUMBER_OF_SLOTS];
	sf::Font font;
public:
	HelpScreen(sf::RenderWindow& window);
	void draw(sf::RenderWindow& window);
};


