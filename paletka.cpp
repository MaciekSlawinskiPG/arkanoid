#include <SFML/Graphics.hpp>
#include "paletka.h"
paletka::paletka(float x_in, float y_in)
{
	position.x = x_in;
	position.y = y_in;
	rectangle.setSize(sf::Vector2f(120.f, 5.f));
	rectangle.setFillColor(sf::Color::Black);
	rectangle.setOutlineThickness(1);
	rectangle.setOutlineColor(sf::Color::White);
	rectangle.setPosition(400,560);
}

void paletka::przesun(float x_in, float y_in)
{
	sf::Vector2f pos;
	pos.x = x_in;
	pos.y = y_in;
	rectangle.move(pos);
}

void paletka::setPos(float x_in, float y_in)
{
	position.x = x_in;
	position.y = y_in;
	rectangle.setPosition(position);

}
