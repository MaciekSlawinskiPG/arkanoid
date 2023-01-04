#pragma once
#include <SFML/Graphics.hpp>

class blok
{
private:
	sf::Vector2f position;
	sf::RectangleShape rectangle;
public:
	blok();
	sf::RectangleShape getBlok() { return rectangle; }
	sf::Vector2f getPos() { return rectangle.getPosition(); }
	void setPos(float x_in, float y_in);

};
