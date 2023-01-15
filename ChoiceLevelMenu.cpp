#include "ChoiceLevelMenu.h"
#include "GameLevels.h"
#include <iostream>

#define MAX_ITEMS 6

ChoiceLevelMenu::ChoiceLevelMenu(float width, float height)
{
	if (!font.loadFromFile("RetroGaming.ttf"))
	{
		std::cout << "wystapil blad podczas wczytywania czcionki" << std::endl;
	}

	menuItem[0].setFont(font);
	menuItem[0].setFillColor(sf::Color::Red);
	menuItem[0].setString("Poziom 1");
	menuItem[0].setPosition(sf::Vector2f(294, height / (MAX_ITEMS + 1) * 1 - 20));

	menuItem[1].setFont(font);
	menuItem[1].setFillColor(sf::Color::White);
	menuItem[1].setString("Poziom 2");
	menuItem[1].setPosition(sf::Vector2f(294, height / (MAX_ITEMS + 1) * 2 - 20));

	menuItem[2].setFont(font);
	menuItem[2].setFillColor(sf::Color::White);
	menuItem[2].setString("Poziom 3");
	menuItem[2].setPosition(sf::Vector2f(294, height / (MAX_ITEMS + 1) * 3 - 20));

	menuItem[3].setFont(font);
	menuItem[3].setFillColor(sf::Color::White);
	menuItem[3].setString("Poziom 4");
	menuItem[3].setPosition(sf::Vector2f(294, height / (MAX_ITEMS + 1) * 4 - 20));

	menuItem[4].setFont(font);
	menuItem[4].setFillColor(sf::Color::White);
	menuItem[4].setString("Poziom 5");
	menuItem[4].setPosition(sf::Vector2f(294, height / (MAX_ITEMS + 1) * 5 - 20));

	menuItem[5].setFont(font);
	menuItem[5].setFillColor(sf::Color::White);
	menuItem[5].setString("Powrot do menu");
	menuItem[5].setPosition(sf::Vector2f(234, height / (MAX_ITEMS + 1) * 6 - 20));

	selectedItemIndex = 0;
}

void ChoiceLevelMenu::draw(sf::RenderWindow& window)
{
	for (int i = 0; i < NUMBER_OF_ITEMS; i++)
	{
		window.draw(menuItem[i]);
	}
}

void ChoiceLevelMenu::MoveUp()
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

void ChoiceLevelMenu::MoveDown()
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

void ChoiceLevelMenu::RunChoiceLevelMenu()
{
	Level1 level[5];
	int Scores = 0;
	sf::ContextSettings settings;
	sf::RenderWindow ChoiceLevelMenuWindow(sf::VideoMode(800, 600), "Arkanoid game", sf::Style::Default, settings);
	ChoiceLevelMenuWindow.setFramerateLimit(60);

	ChoiceLevelMenu LevelMenu(ChoiceLevelMenuWindow.getSize().x, ChoiceLevelMenuWindow.getSize().y);

	while (ChoiceLevelMenuWindow.isOpen())
	{
		sf::Event event;
		while (ChoiceLevelMenuWindow.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				ChoiceLevelMenuWindow.close();
				break;

			case sf::Event::KeyReleased:
				switch (event.key.code)
				{
				case sf::Keyboard::Up:
					LevelMenu.MoveUp();
					break;

				case sf::Keyboard::Down:
					LevelMenu.MoveDown();
					break;

				case sf::Keyboard::Enter:
					switch (LevelMenu.GetSelectedItemIndex())
					{
					case 0:
					{
						std::cout << "Uruchamiam Poziom 1..." << std::endl;
						level[0].RunLevel("blocksPositionLevel1.txt", 100);
						break;
					}
					case 1:
					{
						std::cout << "Uruchamiam Poziom 2..." << std::endl;
						level[1].RunLevel("blocksPositionLevel2.txt", 64);
						break; }
					case 2:
					{
						std::cout << "Uruchamiam Poziom 3..." << std::endl;
						level[2].RunLevel("blocksPositionLevel3.txt", 36);
						break;
					}
					case 3:
					{
						std::cout << "Uruchamiam Poziom 4..." << std::endl;
						level[3].RunLevel("blocksPositionLevel4.txt", 16);
						break;
					}
					case 4:
					{
						std::cout << "Uruchamiam Poziom 5..." << std::endl;
						level[4].RunLevel("blocksPositionLevel5.txt", 4);
						break;
					}
					case 5:
						ChoiceLevelMenuWindow.close();
						break;
					}
				}
			}
		}
		ChoiceLevelMenuWindow.clear();
		LevelMenu.draw(ChoiceLevelMenuWindow);
		ChoiceLevelMenuWindow.display();
	}
}