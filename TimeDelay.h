#pragma once

#include <SFML/Graphics.hpp>
#include <Windows.h>
#include <iostream>

class TimeDelay
{
private:
	sf::Text text[3];
	sf::Font font;

public:
	TimeDelay(sf::RenderWindow& window);
	void turnOnCountdown(sf::RenderWindow& window);
};
