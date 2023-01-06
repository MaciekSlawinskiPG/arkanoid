#include "PauseScreen.h"
#include <iostream>

PauseScreen::PauseScreen(sf::RenderWindow& window)
{

	if (!font.loadFromFile("RetroGaming.ttf"))
	{
		std::cout << "wystapil blad podczas wczytywania czcionki" << std::endl;
	}

	background.setSize(sf::Vector2f(533, 291));
	background.setFillColor(sf::Color::Black);
	background.setOutlineThickness(2);
	background.setOutlineColor(sf::Color::White);
	background.setPosition(137, 122);

	text[0].setFont(font);
	text[0].setFillColor(sf::Color::Red);
	text[0].setString("Czy napewno chcesz\n       opuscic gre?");
	text[0].setPosition(window.getSize().x / 2 - 226, window.getSize().y / 2-150);
	text[0].setCharacterSize(35);

	text[1].setFont(font);
	text[1].setFillColor(sf::Color::White);
	text[1].setString(" TAK \n[ESC]");
	text[1].setPosition(window.getSize().x / 2 - 213, window.getSize().y / 2+15);
	text[1].setCharacterSize(25);

	text[2].setFont(font);
	text[2].setFillColor(sf::Color::White);
	text[2].setString("    NIE \n[RETURN]");
	text[2].setPosition(window.getSize().x / 2 +77 , window.getSize().y / 2 + 15);
	text[2].setCharacterSize(25);
}

void PauseScreen::draw(sf::RenderWindow& window)
{
	window.draw(background);

	for (int i = 0; i < MAX_NUMBER_OF_SLOTS; i++)
	{
		window.draw(text[i]);
	}
}
