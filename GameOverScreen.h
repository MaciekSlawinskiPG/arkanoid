#pragma once
#include <SFML/Graphics.hpp>

#define MAX_NUMBER_OF_SLOTS 2
class GameOverScreen
{
private:
	sf::RectangleShape background;
	sf::Text text[MAX_NUMBER_OF_SLOTS];
	sf::Font font;
public:
	GameOverScreen(sf::RenderWindow& window);
	void draw(sf::RenderWindow& window);
};

