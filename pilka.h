#pragma once
#include <SFML/Graphics.hpp>

class pilka
{
private:
	sf::Vector2f position;
	float xVel = 10;
	float yVel = 10;
	sf::CircleShape ball;
public:
	pilka(float x_in, float y_in);
	void przesun(float x_in, float y_in);
	sf::CircleShape getPilka() { return ball; }
	sf::Vector2f getPos() { return ball.getPosition(); }
	void setPos(float x_in, float y_in);
};

