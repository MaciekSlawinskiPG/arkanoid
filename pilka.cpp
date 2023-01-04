#include <SFML/Graphics.hpp>
#include "pilka.h"
pilka::pilka(float x_in, float y_in)
{
	position.x = x_in;
	position.y = y_in;
	ball.setRadius(5);
	ball.setFillColor(sf::Color(150, 50, 250));
	ball.setOutlineThickness(1);
	ball.setOutlineColor(sf::Color::Yellow);
	ball.setPosition(position);
}

void pilka::przesun(float x_in, float y_in)
{
	sf::Vector2f pos;
	pos.x = x_in;
	pos.y = y_in;
	ball.move(pos);
}

void pilka::setPos(float x_in, float y_in)
{
	position.x = x_in;
	position.y = y_in;
	ball.setPosition(position);
}
