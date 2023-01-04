#include <iostream>
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include "pilka.h"
#include "paletka.h"
#include "blok.h"
#include "PlayGame.h"
#include <string>

bool PlayGame::isCollide(pilka s1, blok s2)
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

PlayGame::PlayGame()
{
	sf::ContextSettings settings;
	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!", sf::Style::Default, settings);
	window.setFramerateLimit(60);

	pilka p1(400, 300);
	paletka pal1(300, 300);
	int x = 0, y = 0;
	int dx = 7, dy = 5;
	int score = 0;
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

	blok block[200];
	int n = 0;
	for (int i = 1; i <= 10; i++)
		for (int j = 1; j <= 10; j++)
		{
			block[n].setPos(i * 50+120, j * 26);
			n++;
		}

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		if (p1.getPos().x > (window.getSize().x) - radiusWithOutline || p1.getPos().x < 4) dx = -dx;
		if (p1.getPos().y > (window.getSize().y) - radiusWithOutline || p1.getPos().y < 4) dy = -dy;
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

		sf::Vector2i localPosition = sf::Mouse::getPosition(window);
		pal1.setPos(localPosition.x, 560);

		window.clear();
		window.draw(p1.getPilka());
		window.draw(pal1.getPaletka());
		window.draw(scores);

		for (int k = 0; k < n; k++)
			window.draw(block[k].getBlok());

		window.display();
	}
}
