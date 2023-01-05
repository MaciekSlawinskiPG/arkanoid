#include "menu.h"
#include <iostream>

menu::menu(float width, float height)
{
	if (!font.loadFromFile("RetroGaming.ttf"))
	{
		std::cout << "wystapil blad podczas wczytywania czcionki" << std::endl;
	}

	menuItem[0].setFont(font);
	menuItem[0].setFillColor(sf::Color::Red);
	menuItem[0].setString("Rozpocznij gre");
	menuItem[0].setPosition(sf::Vector2f(257, height / (NUMBER_OF_ITEMS + 1) * 1-20));

	menuItem[1].setFont(font);
	menuItem[1].setFillColor(sf::Color::White);
	menuItem[1].setString("Ranking");
	menuItem[1].setPosition(sf::Vector2f(330, height / (NUMBER_OF_ITEMS + 1) * 2-20));

	menuItem[2].setFont(font);
	menuItem[2].setFillColor(sf::Color::White);
	menuItem[2].setString("Wyjdz");
	menuItem[2].setPosition(sf::Vector2f(345, height / (NUMBER_OF_ITEMS + 1) * 3-20));

	selectedItemIndex = 0;
}

void menu::draw(sf::RenderWindow& window)
{
	for (int i = 0; i < NUMBER_OF_ITEMS; i++)
	{
		window.draw(menuItem[i]);
	}
}

void menu::MoveUp()
{
	if (selectedItemIndex - 1 >= 0)
	{
		menuItem[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex--;
		menuItem[selectedItemIndex].setFillColor(sf::Color::Red);
	 }
	else
	{
		menuItem[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex = NUMBER_OF_ITEMS - 1;
		menuItem[selectedItemIndex].setFillColor(sf::Color::Red);

	}
}

void menu::MoveDown()
{
	if (selectedItemIndex + 1 < NUMBER_OF_ITEMS)
	{
		menuItem[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex++;
		menuItem[selectedItemIndex].setFillColor(sf::Color::Red);
	}
	else
	{
		menuItem[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex = 0;
		menuItem[selectedItemIndex].setFillColor(sf::Color::Red);
	}
}
