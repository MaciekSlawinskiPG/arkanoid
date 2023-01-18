#pragma once
#include "SFML/Graphics.hpp"


#define NUMBER_OF_ITEMS 6
class RankingScreen
{
private:
	sf::Font font;
	sf::Text menuItem[NUMBER_OF_ITEMS];

public:
	RankingScreen(float width, float height);
	void draw(sf::RenderWindow& window);
	void RunRankingScreen();

};