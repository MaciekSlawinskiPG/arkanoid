#pragma once
#include "SFML/Graphics.hpp"

#define NUMBER_OF_ITEMS 3
class menu
{
private:
	int selectedItemIndex;
	sf::Font font;
	sf::Text menuItem[NUMBER_OF_ITEMS];

public:
	menu(float width, float height);
	void draw(sf::RenderWindow &window);
	void MoveUp();
	void MoveDown();
	int GetSelectedItemIndex() { return selectedItemIndex; }
	
};

