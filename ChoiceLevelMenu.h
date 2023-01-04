#pragma once
#include "SFML/Graphics.hpp"


#define NUMBER_OF_ITEMS 6
class ChoiceLevelMenu
{
private:
	int selectedItemIndex;
	sf::Font font;
	sf::Text menuItem[NUMBER_OF_ITEMS];

public:
	ChoiceLevelMenu(float width, float height);
	void draw(sf::RenderWindow& window);
	void MoveUp();
	void MoveDown();
	int GetSelectedItemIndex() { return selectedItemIndex; }
	void RunChoiceLevelMenu();

};