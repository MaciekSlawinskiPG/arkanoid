#pragma once
#include "SFML/Graphics.hpp"
#define MAX_NUMBER_OF_SLOTS 3
class NextLevelScreen
{
private:
	sf::RectangleShape background;
	sf::Text text[MAX_NUMBER_OF_SLOTS];
	sf::Font font;
public:
	NextLevelScreen(sf::RenderWindow& window);
	void draw(sf::RenderWindow& window);
};
