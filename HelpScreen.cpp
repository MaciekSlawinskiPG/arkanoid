#include "HelpScreen.h"
#include <iostream>

HelpScreen::HelpScreen(sf::RenderWindow& window)
{

	if (!font.loadFromFile("RetroGaming.ttf"))
	{
		std::cout << "wystapil blad podczas wczytywania czcionki" << std::endl;
	}

	text[0].setFont(font);
	text[0].setFillColor(sf::Color::Red);
	text[0].setString("! ZASADY GRY !");
	text[0].setPosition(window.getSize().x / 2.0 - 149.5, 95.0);
	text[0].setCharacterSize(35);

	text[1].setFont(font);
	text[1].setFillColor(sf::Color::White);
	text[1].setString("Celem gry jest zbicie wszystkich blokow");
	text[1].setPosition(window.getSize().x / 2.0 - 308.5, 191.0);
	text[1].setCharacterSize(25);

	text[2].setFont(font);
	text[2].setFillColor(sf::Color::White);
	text[2].setString("Masz na to tylko jedno zycie,\n        wiec badz ostrozny!");
	text[2].setPosition(window.getSize().x / 2.0 - 225.5, 241);
	text[2].setCharacterSize(25);

	text[3].setFont(font);
	text[3].setFillColor(sf::Color::White);
	text[3].setString("Aby zapauzowac gre w jej trakcie,\n            wcisnij klawisz [ESC]");
	text[3].setPosition(window.getSize().x / 2.0 - 266.5, 326);
	text[3].setCharacterSize(25);

	text[4].setFont(font);
	text[4].setFillColor(sf::Color::White);
	text[4].setString("[F1] kontynuuj gre");
	text[4].setPosition(window.getSize().x / 2.0 - 143, 520);
	text[4].setCharacterSize(25);
}

void HelpScreen::draw(sf::RenderWindow& window)
{
	for (int i = 0; i < MAX_NUMBER_OF_SLOTS; i++)
	{
		window.draw(text[i]);
	}
}
