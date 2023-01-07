#include "GameOverScreen.h"
#include <iostream>

GameOverScreen::GameOverScreen(sf::RenderWindow& window)
{
	if (!font.loadFromFile("RetroGaming.ttf"))
	{
		std::cout << "wystapil blad podczas wczytywania czcionki" << std::endl;
	}
	background.setSize(sf::Vector2f(631, 179));
	background.setFillColor(sf::Color::Black);
	background.setOutlineThickness(2);
	background.setOutlineColor(sf::Color::White);
	background.setPosition(93, 222);

	text[0].setFont(font);
	text[0].setFillColor(sf::Color::Red);
	text[0].setString("|| GAME OVER ||");
	text[0].setPosition(window.getSize().x / 2.0 - 149, 262.0);
	text[0].setCharacterSize(35);

	text[1].setFont(font);
	text[1].setFillColor(sf::Color::White);
	text[1].setString("Nacisnij [ESC] aby rozpoczac od nowa");
	text[1].setPosition(window.getSize().x / 2.0 - 295.5, 333.0);
	text[1].setCharacterSize(25);
}
void GameOverScreen::draw(sf::RenderWindow& window)
{
	window.draw(background);
	for (int i = 0; i < MAX_NUMBER_OF_SLOTS; i++)
	{
		window.draw(text[i]);
	}
}
