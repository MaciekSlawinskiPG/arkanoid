#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include "menu.h"
#include "PlayGame.h"
#include "ChoiceLevelMenu.h"

int main()
{
	sf::ContextSettings settings;
	sf::RenderWindow window(sf::VideoMode(800, 600), "Arkanoid game", sf::Style::Default, settings);
	window.setFramerateLimit(60);

	menu menu(window.getSize().x, window.getSize().y);
	ChoiceLevelMenu LevelMenu(window.getSize().x, window.getSize().y);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;

			case sf::Event::KeyReleased:
				switch (event.key.code)
				{
				case sf::Keyboard::Up:
					menu.MoveUp();
					break;

				case sf::Keyboard::Down:
					menu.MoveDown();
					break;

				case sf::Keyboard::Enter:
					switch (menu.GetSelectedItemIndex())
					{
					case 0:
					{
						LevelMenu.RunChoiceLevelMenu();
						break; 
					}	
					case 1:
						std::cout << "Przedstawiam zasady gry..." << std::endl;
						break;
					case 2:
						window.close();
						break;
					}
				}
			}
		}
		window.clear();
		menu.draw(window);
		window.display();
	}
	return 0;
}