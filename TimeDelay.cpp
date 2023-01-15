#include <SFML/Graphics.hpp>
#include <Windows.h>
#include <iostream>
#include "TimeDelay.h"

TimeDelay::TimeDelay(sf::RenderWindow& window)
{

	if (!font.loadFromFile("RetroGaming.ttf"))
	{
		std::cout << "wystapil blad podczas wczytywania czcionki" << std::endl;
	}

	text[0].setFont(font);
	text[0].setFillColor(sf::Color::Red);
	text[0].setString("3");
	text[0].setPosition(window.getSize().x / 2.0, window.getSize().y / 2.0);
	text[0].setCharacterSize(35);

	text[1].setFont(font);
	text[1].setFillColor(sf::Color::Red);
	text[1].setString("2");
	text[1].setPosition(window.getSize().x / 2.0, window.getSize().y / 2.0);
	text[1].setCharacterSize(35);

	text[2].setFont(font);
	text[2].setFillColor(sf::Color::Red);
	text[2].setString("1");
	text[2].setPosition(window.getSize().x / 2.0, window.getSize().y / 2.0);
	text[2].setCharacterSize(35);
}
void TimeDelay::turnOnCountdown(sf::RenderWindow& window)
{
	window.draw(text[0]);
	window.display();
	Sleep(1000);

	window.draw(text[1]);
	window.display();
	Sleep(1000);

	window.draw(text[2]);
	window.display();
	Sleep(1000);

}