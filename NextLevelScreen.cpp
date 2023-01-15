#include "NextLevelScreen.h"
#include <iostream>

NextLevelScreen::NextLevelScreen(sf::RenderWindow& window)
{

	if (!font.loadFromFile("RetroGaming.ttf"))
	{
		std::cout << "wystapil blad podczas wczytywania czcionki" << std::endl;
	}

	background.setSize(sf::Vector2f(580, 214));
	background.setFillColor(sf::Color::Black);
	background.setOutlineThickness(2);
	background.setOutlineColor(sf::Color::White);
	background.setPosition(108, 192);

	text[0].setFont(font);
	text[0].setFillColor(sf::Color::Red);
	text[0].setString("Poziom ukonczony!");
	text[0].setPosition(window.getSize().x / 2.0 - 215.5, 222);
	text[0].setCharacterSize(35);

	text[1].setFont(font);
	text[1].setFillColor(sf::Color::White);
	text[1].setString("Powrot do menu \n        [ESC]");
	text[1].setPosition(window.getSize().x / 2.0 - 262, 325);
	text[1].setCharacterSize(25);

	text[2].setFont(font);
	text[2].setFillColor(sf::Color::White);
	text[2].setString("Nastepny Poziom \n     [ENTER]");
	text[2].setPosition(window.getSize().x / 2.0 + 1, 325);
	text[2].setCharacterSize(25);
}

void NextLevelScreen::draw(sf::RenderWindow& window)
{
	window.draw(background);
	for (int i = 0; i < MAX_NUMBER_OF_SLOTS; i++)
	{
		window.draw(text[i]);
	}
}
