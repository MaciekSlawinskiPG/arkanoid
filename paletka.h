#pragma once
#include <SFML/Graphics.hpp>

class paletka
{
private:
	sf::Vector2f position;
	sf::RectangleShape rectangle;
public:
	paletka(float x_in, float y_in, float size_x, float size_y);
	void przesun(float x_in, float y_in);
	sf::RectangleShape getPaletka() { return rectangle; }
	sf::Vector2f getPos() { return rectangle.getPosition(); }
	void setPos(float x_in, float y_in);
};
