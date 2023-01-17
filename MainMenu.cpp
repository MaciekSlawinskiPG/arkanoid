#include "MainMenu.h"

MainMenu::MainMenu()
{
	sf::ContextSettings settings;
	sf::RenderWindow MainWindow(sf::VideoMode(800, 600), "Arkanoid game", sf::Style::Default, settings);
	MainWindow.setFramerateLimit(60);

	sf::Texture texture;
	texture.loadFromFile("background.jpg");
	sf::Sprite backgroundImage;
	backgroundImage.setTexture(texture);

	menu menu(MainWindow.getSize().x, MainWindow.getSize().y);
	ChoiceLevelMenu LevelMenu(MainWindow.getSize().x, MainWindow.getSize().y);


	while (MainWindow.isOpen())
	{
		sf::Event event;
		while (MainWindow.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				MainWindow.close();
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
						std::cout << "Uruchamiam ranking graczy..." << std::endl;
						break;
					case 2:
						MainWindow.close();
						break;
					}
				}
			}
		}
		MainWindow.clear();
		MainWindow.draw(backgroundImage);
		menu.draw(MainWindow);
		MainWindow.display();
	}
}
