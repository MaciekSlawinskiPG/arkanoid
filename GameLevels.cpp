#include <iostream>
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <string>

#include "pilka.h"
#include "paletka.h"
#include "blok.h"
#include "GameLevels.h"
#include "PauseScreen.h"
#include "HelpScreen.h"

bool isCollide(pilka s1, blok s2)
{
	if ((s1.getPos().x > s2.getPos().x) && (s1.getPos().x < ((s2.getPos().x) + 43)) && (s1.getPos().y > s2.getPos().y - 10) && (s1.getPos().y < (s2.getPos().y) + 20)) 
	{ 
		return true; 
	}
	else 
	{ 
		return false; 
	}
}
Level1::Level1()
{
	sf::ContextSettings settings;
	sf::RenderWindow PlayGameWindow(sf::VideoMode(800, 600), "SFML works!", sf::Style::Default, settings);
	PlayGameWindow.setFramerateLimit(60);

	pilka p1(400, 300);
	paletka pal1(300, 300,120,5);
	int x = 0, y = 0;
	int dx = 7, dy = 5;
	int score = 0;
	int WhichKeyIsPressed = 0;
	bool wait = true;
	std::string str = std::to_string(score);
	int radiusWithOutline = 2 * ((p1.getPilka().getRadius()) + (p1.getPilka().getOutlineThickness()));
	sf::Font font;
	if (!font.loadFromFile("RetroGaming.ttf"))
	{
		std::cout << "wystapil blad podczas wczytywania czcionki" << std::endl;
	}
	sf::Text scores;
	scores.setFont(font);
	scores.setFillColor(sf::Color::White);
	scores.setString(str);
	scores.setPosition(20, 20);
	scores.setCharacterSize(20);


	PauseScreen loadPauseScreen(PlayGameWindow);
	HelpScreen loadHelpScreen(PlayGameWindow);

	blok block[100];
	int n = 0;
	for (int i = 1; i <= 10; i++)
		for (int j = 1; j <= 10; j++)
		{
			block[n].setPos(i * 50+120, j * 26);
			n++;
		}

	while (PlayGameWindow.isOpen())
	{
		sf::Event event;
		while (PlayGameWindow.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				PlayGameWindow.close();
			else
				if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Escape)
				{
					wait = !wait;
					event.key.code = sf::Keyboard::Q;
					WhichKeyIsPressed = 1;
				}
				if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::F1)
				{
					wait = !wait;
					event.key.code = sf::Keyboard::Q;
					WhichKeyIsPressed = 2;
				}

		}
		if (!wait)
		{
			switch (WhichKeyIsPressed)
			{
				case 1:
				{
					
					loadPauseScreen.draw(PlayGameWindow);
					PlayGameWindow.display();
					break;
				}
				case 2:
				{
					PlayGameWindow.clear();
					loadHelpScreen.draw(PlayGameWindow);
					PlayGameWindow.display();
					break;
				}
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				PlayGameWindow.close();
			}


			if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Backspace)
			{
				wait = true;
			}
		}
		else {
			if (p1.getPos().x > (PlayGameWindow.getSize().x) - radiusWithOutline || p1.getPos().x < 4) dx = -dx;
			if (p1.getPos().y > (PlayGameWindow.getSize().y) - radiusWithOutline || p1.getPos().y < 4) dy = -dy;
			if ((p1.getPos().x > pal1.getPos().x) && (p1.getPos().x < ((pal1.getPos().x) + 120)) && (p1.getPos().y > pal1.getPos().y - 10) && (p1.getPos().y < (pal1.getPos().y) + 5))
				dy = -(rand() % 3 + 4);

			p1.przesun(dx, 0);
			for (int i = 0; i < n; i++)
				if (isCollide(p1, block[i]))
				{
					block[i].setPos(-100, 0);
					dx = -dx;
					score++;
					std::string str = std::to_string(score);
					scores.setString(str);
					std::cout << "score: " << score << std::endl;

				}

			p1.przesun(0, dy);
			for (int i = 0; i < n; i++)
				if (isCollide(p1, block[i]))
				{
					block[i].setPos(-100, 0);
					dy = -dy;
					score++;
					std::string str = std::to_string(score);
					scores.setString(str);
					std::cout << "score: " << score << std::endl;
				}

			sf::Vector2i localPosition = sf::Mouse::getPosition(PlayGameWindow);
			pal1.setPos(localPosition.x, 560);

			PlayGameWindow.clear();
			PlayGameWindow.draw(p1.getPilka());
			PlayGameWindow.draw(pal1.getPaletka());
			PlayGameWindow.draw(scores);

			for (int k = 0; k < n; k++)
				PlayGameWindow.draw(block[k].getBlok());

			PlayGameWindow.display();
		}
	}
}
Level2::Level2()
{
	sf::ContextSettings settings;
	sf::RenderWindow PlayGameWindow(sf::VideoMode(800, 600), "SFML works!", sf::Style::Default, settings);
	PlayGameWindow.setFramerateLimit(60);

	pilka p1(400, 300);
	paletka pal1(300, 300, 120, 5);
	int x = 0, y = 0;
	int dx = 7, dy = 5;
	int score = 0;
	int WhichKeyIsPressed = 0;
	bool wait = true;
	std::string str = std::to_string(score);
	int radiusWithOutline = 2 * ((p1.getPilka().getRadius()) + (p1.getPilka().getOutlineThickness()));
	sf::Font font;
	if (!font.loadFromFile("RetroGaming.ttf"))
	{
		std::cout << "wystapil blad podczas wczytywania czcionki" << std::endl;
	}
	sf::Text scores;
	scores.setFont(font);
	scores.setFillColor(sf::Color::White);
	scores.setString(str);
	scores.setPosition(20, 20);
	scores.setCharacterSize(20);


	PauseScreen loadPauseScreen(PlayGameWindow);
	HelpScreen loadHelpScreen(PlayGameWindow);

	blok block[100];
	int n = 0;
	for (int i = 1; i <= 8; i++)
		for (int j = 1; j <= 8; j++)
		{
			block[n].setPos(i * 50 + 120, j * 26);
			n++;
		}

	while (PlayGameWindow.isOpen())
	{
		sf::Event event;
		while (PlayGameWindow.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				PlayGameWindow.close();
			else
				if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Escape)
				{
					wait = !wait;
					event.key.code = sf::Keyboard::Q;
					WhichKeyIsPressed = 1;
				}
			if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::F1)
			{
				wait = !wait;
				event.key.code = sf::Keyboard::Q;
				WhichKeyIsPressed = 2;
			}

		}
		if (!wait)
		{
			switch (WhichKeyIsPressed)
			{
			case 1:
			{
				PlayGameWindow.clear();
				loadPauseScreen.draw(PlayGameWindow);
				PlayGameWindow.display();
				break;
			}
			case 2:
			{
				PlayGameWindow.clear();
				loadHelpScreen.draw(PlayGameWindow);
				PlayGameWindow.display();
				break;
			}
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				PlayGameWindow.close();
			}


			if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Backspace)
			{
				wait = true;
			}
		}
		else {
			if (p1.getPos().x > (PlayGameWindow.getSize().x) - radiusWithOutline || p1.getPos().x < 4) dx = -dx;
			if (p1.getPos().y > (PlayGameWindow.getSize().y) - radiusWithOutline || p1.getPos().y < 4) dy = -dy;
			if ((p1.getPos().x > pal1.getPos().x) && (p1.getPos().x < ((pal1.getPos().x) + 120)) && (p1.getPos().y > pal1.getPos().y - 10) && (p1.getPos().y < (pal1.getPos().y) + 5))
				dy = -(rand() % 3 + 4);

			p1.przesun(dx, 0);
			for (int i = 0; i < n; i++)
				if (isCollide(p1, block[i]))
				{
					block[i].setPos(-100, 0);
					dx = -dx;
					score++;
					std::string str = std::to_string(score);
					scores.setString(str);
					std::cout << "score: " << score << std::endl;

				}

			p1.przesun(0, dy);
			for (int i = 0; i < n; i++)
				if (isCollide(p1, block[i]))
				{
					block[i].setPos(-100, 0);
					dy = -dy;
					score++;
					std::string str = std::to_string(score);
					scores.setString(str);
					std::cout << "score: " << score << std::endl;
				}

			sf::Vector2i localPosition = sf::Mouse::getPosition(PlayGameWindow);
			pal1.setPos(localPosition.x, 560);

			PlayGameWindow.clear();
			PlayGameWindow.draw(p1.getPilka());
			PlayGameWindow.draw(pal1.getPaletka());
			PlayGameWindow.draw(scores);

			for (int k = 0; k < n; k++)
				PlayGameWindow.draw(block[k].getBlok());

			PlayGameWindow.display();
		}
	}
}
Level3::Level3()
{
	sf::ContextSettings settings;
	sf::RenderWindow PlayGameWindow(sf::VideoMode(800, 600), "SFML works!", sf::Style::Default, settings);
	PlayGameWindow.setFramerateLimit(60);

	pilka p1(400, 300);
	paletka pal1(300, 300, 120, 5);
	int x = 0, y = 0;
	int dx = 7, dy = 5;
	int score = 0;
	int WhichKeyIsPressed = 0;
	bool wait = true;
	std::string str = std::to_string(score);
	int radiusWithOutline = 2 * ((p1.getPilka().getRadius()) + (p1.getPilka().getOutlineThickness()));
	sf::Font font;
	if (!font.loadFromFile("RetroGaming.ttf"))
	{
		std::cout << "wystapil blad podczas wczytywania czcionki" << std::endl;
	}
	sf::Text scores;
	scores.setFont(font);
	scores.setFillColor(sf::Color::White);
	scores.setString(str);
	scores.setPosition(20, 20);
	scores.setCharacterSize(20);


	PauseScreen loadPauseScreen(PlayGameWindow);
	HelpScreen loadHelpScreen(PlayGameWindow);

	blok block[100];
	int n = 0;
	for (int i = 1; i <= 6; i++)
		for (int j = 1; j <= 6; j++)
		{
			block[n].setPos(i * 50 + 120, j * 26);
			n++;
		}

	while (PlayGameWindow.isOpen())
	{
		sf::Event event;
		while (PlayGameWindow.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				PlayGameWindow.close();
			else
				if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Escape)
				{
					wait = !wait;
					event.key.code = sf::Keyboard::Q;
					WhichKeyIsPressed = 1;
				}
			if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::F1)
			{
				wait = !wait;
				event.key.code = sf::Keyboard::Q;
				WhichKeyIsPressed = 2;
			}

		}
		if (!wait)
		{
			switch (WhichKeyIsPressed)
			{
			case 1:
			{
				PlayGameWindow.clear();
				loadPauseScreen.draw(PlayGameWindow);
				PlayGameWindow.display();
				break;
			}
			case 2:
			{
				PlayGameWindow.clear();
				loadHelpScreen.draw(PlayGameWindow);
				PlayGameWindow.display();
				break;
			}
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				PlayGameWindow.close();
			}


			if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Backspace)
			{
				wait = true;
			}
		}
		else {
			if (p1.getPos().x > (PlayGameWindow.getSize().x) - radiusWithOutline || p1.getPos().x < 4) dx = -dx;
			if (p1.getPos().y > (PlayGameWindow.getSize().y) - radiusWithOutline || p1.getPos().y < 4) dy = -dy;
			if ((p1.getPos().x > pal1.getPos().x) && (p1.getPos().x < ((pal1.getPos().x) + 120)) && (p1.getPos().y > pal1.getPos().y - 10) && (p1.getPos().y < (pal1.getPos().y) + 5))
				dy = -(rand() % 3 + 4);

			p1.przesun(dx, 0);
			for (int i = 0; i < n; i++)
				if (isCollide(p1, block[i]))
				{
					block[i].setPos(-100, 0);
					dx = -dx;
					score++;
					std::string str = std::to_string(score);
					scores.setString(str);
					std::cout << "score: " << score << std::endl;

				}

			p1.przesun(0, dy);
			for (int i = 0; i < n; i++)
				if (isCollide(p1, block[i]))
				{
					block[i].setPos(-100, 0);
					dy = -dy;
					score++;
					std::string str = std::to_string(score);
					scores.setString(str);
					std::cout << "score: " << score << std::endl;
				}

			sf::Vector2i localPosition = sf::Mouse::getPosition(PlayGameWindow);
			pal1.setPos(localPosition.x, 560);

			PlayGameWindow.clear();
			PlayGameWindow.draw(p1.getPilka());
			PlayGameWindow.draw(pal1.getPaletka());
			PlayGameWindow.draw(scores);

			for (int k = 0; k < n; k++)
				PlayGameWindow.draw(block[k].getBlok());

			PlayGameWindow.display();
		}
	}
}
Level4::Level4()
{
	sf::ContextSettings settings;
	sf::RenderWindow PlayGameWindow(sf::VideoMode(800, 600), "SFML works!", sf::Style::Default, settings);
	PlayGameWindow.setFramerateLimit(60);

	pilka p1(400, 300);
	paletka pal1(300, 300, 120, 5);
	int x = 0, y = 0;
	int dx = 7, dy = 5;
	int score = 0;
	int WhichKeyIsPressed = 0;
	bool wait = true;
	std::string str = std::to_string(score);
	int radiusWithOutline = 2 * ((p1.getPilka().getRadius()) + (p1.getPilka().getOutlineThickness()));
	sf::Font font;
	if (!font.loadFromFile("RetroGaming.ttf"))
	{
		std::cout << "wystapil blad podczas wczytywania czcionki" << std::endl;
	}
	sf::Text scores;
	scores.setFont(font);
	scores.setFillColor(sf::Color::White);
	scores.setString(str);
	scores.setPosition(20, 20);
	scores.setCharacterSize(20);


	PauseScreen loadPauseScreen(PlayGameWindow);
	HelpScreen loadHelpScreen(PlayGameWindow);

	blok block[100];
	int n = 0;
	for (int i = 1; i <= 4; i++)
		for (int j = 1; j <= 4; j++)
		{
			block[n].setPos(i * 50 + 120, j * 26);
			n++;
		}

	while (PlayGameWindow.isOpen())
	{
		sf::Event event;
		while (PlayGameWindow.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				PlayGameWindow.close();
			else
				if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Escape)
				{
					wait = !wait;
					event.key.code = sf::Keyboard::Q;
					WhichKeyIsPressed = 1;
				}
			if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::F1)
			{
				wait = !wait;
				event.key.code = sf::Keyboard::Q;
				WhichKeyIsPressed = 2;
			}

		}
		if (!wait)
		{
			switch (WhichKeyIsPressed)
			{
			case 1:
			{
				PlayGameWindow.clear();
				loadPauseScreen.draw(PlayGameWindow);
				PlayGameWindow.display();
				break;
			}
			case 2:
			{
				PlayGameWindow.clear();
				loadHelpScreen.draw(PlayGameWindow);
				PlayGameWindow.display();
				break;
			}
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				PlayGameWindow.close();
			}


			if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Backspace)
			{
				wait = true;
			}
		}
		else {
			if (p1.getPos().x > (PlayGameWindow.getSize().x) - radiusWithOutline || p1.getPos().x < 4) dx = -dx;
			if (p1.getPos().y > (PlayGameWindow.getSize().y) - radiusWithOutline || p1.getPos().y < 4) dy = -dy;
			if ((p1.getPos().x > pal1.getPos().x) && (p1.getPos().x < ((pal1.getPos().x) + 120)) && (p1.getPos().y > pal1.getPos().y - 10) && (p1.getPos().y < (pal1.getPos().y) + 5))
				dy = -(rand() % 3 + 4);

			p1.przesun(dx, 0);
			for (int i = 0; i < n; i++)
				if (isCollide(p1, block[i]))
				{
					block[i].setPos(-100, 0);
					dx = -dx;
					score++;
					std::string str = std::to_string(score);
					scores.setString(str);
					std::cout << "score: " << score << std::endl;

				}

			p1.przesun(0, dy);
			for (int i = 0; i < n; i++)
				if (isCollide(p1, block[i]))
				{
					block[i].setPos(-100, 0);
					dy = -dy;
					score++;
					std::string str = std::to_string(score);
					scores.setString(str);
					std::cout << "score: " << score << std::endl;
				}

			sf::Vector2i localPosition = sf::Mouse::getPosition(PlayGameWindow);
			pal1.setPos(localPosition.x, 560);

			PlayGameWindow.clear();
			PlayGameWindow.draw(p1.getPilka());
			PlayGameWindow.draw(pal1.getPaletka());
			PlayGameWindow.draw(scores);

			for (int k = 0; k < n; k++)
				PlayGameWindow.draw(block[k].getBlok());

			PlayGameWindow.display();
		}
	}
}
Level5::Level5()
{
	sf::ContextSettings settings;
	sf::RenderWindow PlayGameWindow(sf::VideoMode(800, 600), "SFML works!", sf::Style::Default, settings);
	PlayGameWindow.setFramerateLimit(60);

	pilka p1(400, 300);
	paletka pal1(300, 300, 120, 5);
	int x = 0, y = 0;
	int dx = 7, dy = 5;
	int score = 0;
	int WhichKeyIsPressed = 0;
	bool wait = true;
	std::string str = std::to_string(score);
	int radiusWithOutline = 2 * ((p1.getPilka().getRadius()) + (p1.getPilka().getOutlineThickness()));
	sf::Font font;
	if (!font.loadFromFile("RetroGaming.ttf"))
	{
		std::cout << "wystapil blad podczas wczytywania czcionki" << std::endl;
	}
	sf::Text scores;
	scores.setFont(font);
	scores.setFillColor(sf::Color::White);
	scores.setString(str);
	scores.setPosition(20, 20);
	scores.setCharacterSize(20);


	PauseScreen loadPauseScreen(PlayGameWindow);
	HelpScreen loadHelpScreen(PlayGameWindow);

	blok block[100];
	int n = 0;
	for (int i = 1; i <= 3; i++)
		for (int j = 1; j <= 3; j++)
		{
			block[n].setPos(i * 50 + 120, j * 26);
			n++;
		}

	while (PlayGameWindow.isOpen())
	{
		sf::Event event;
		while (PlayGameWindow.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				PlayGameWindow.close();
			else
				if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Escape)
				{
					wait = !wait;
					event.key.code = sf::Keyboard::Q;
					WhichKeyIsPressed = 1;
				}
			if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::F1)
			{
				wait = !wait;
				event.key.code = sf::Keyboard::Q;
				WhichKeyIsPressed = 2;
			}

		}
		if (!wait)
		{
			switch (WhichKeyIsPressed)
			{
			case 1:
			{
				PlayGameWindow.clear();
				loadPauseScreen.draw(PlayGameWindow);
				PlayGameWindow.display();
				break;
			}
			case 2:
			{
				PlayGameWindow.clear();
				loadHelpScreen.draw(PlayGameWindow);
				PlayGameWindow.display();
				break;
			}
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				PlayGameWindow.close();
			}


			if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Backspace)
			{
				wait = true;
			}
		}
		else {
			if (p1.getPos().x > (PlayGameWindow.getSize().x) - radiusWithOutline || p1.getPos().x < 4) dx = -dx;
			if (p1.getPos().y > (PlayGameWindow.getSize().y) - radiusWithOutline || p1.getPos().y < 4) dy = -dy;
			if ((p1.getPos().x > pal1.getPos().x) && (p1.getPos().x < ((pal1.getPos().x) + 120)) && (p1.getPos().y > pal1.getPos().y - 10) && (p1.getPos().y < (pal1.getPos().y) + 5))
				dy = -(rand() % 3 + 4);

			p1.przesun(dx, 0);
			for (int i = 0; i < n; i++)
				if (isCollide(p1, block[i]))
				{
					block[i].setPos(-100, 0);
					dx = -dx;
					score++;
					std::string str = std::to_string(score);
					scores.setString(str);
					std::cout << "score: " << score << std::endl;

				}

			p1.przesun(0, dy);
			for (int i = 0; i < n; i++)
				if (isCollide(p1, block[i]))
				{
					block[i].setPos(-100, 0);
					dy = -dy;
					score++;
					std::string str = std::to_string(score);
					scores.setString(str);
					std::cout << "score: " << score << std::endl;
				}

			sf::Vector2i localPosition = sf::Mouse::getPosition(PlayGameWindow);
			pal1.setPos(localPosition.x, 560);

			PlayGameWindow.clear();
			PlayGameWindow.draw(p1.getPilka());
			PlayGameWindow.draw(pal1.getPaletka());
			PlayGameWindow.draw(scores);

			for (int k = 0; k < n; k++)
				PlayGameWindow.draw(block[k].getBlok());

			PlayGameWindow.display();
		}
	}
}