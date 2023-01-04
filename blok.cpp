#include <SFML/Graphics.hpp>
#include "blok.h"
blok::blok()
{
	rectangle.setSize(sf::Vector2f(43.f, 20.f));
	rectangle.setFillColor(sf::Color::Black);
	rectangle.setOutlineThickness(1);
	rectangle.setOutlineColor(sf::Color::White);
	rectangle.setPosition(-100,-100);
}

void blok::setPos(float x_in, float y_in)
{
	position.x = x_in;
	position.y = y_in;
	rectangle.setPosition(position);
}