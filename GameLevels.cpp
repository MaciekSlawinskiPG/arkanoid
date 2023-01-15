#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <string>
#include <Windows.h>

#include "pilka.h"
#include "paletka.h"
#include "blok.h"
#include "GameLevels.h"
#include "PauseScreen.h"
#include "HelpScreen.h"
#include "GameOverScreen.h"
#include "NextLevelScreen.h"

#define MAX_POINTS_IN_ROUND 4

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
void Level1::SetTestScores(int scores)
{
	testScores = scores;
}
void Level1::RunLevel(std::string nameOfFile, int blocks)
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
	int TimeFlag = 0;
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
	GameOverScreen loadGameOverScreen(PlayGameWindow);
	NextLevelScreen loadNextLevelScreen(PlayGameWindow);


	blok block[100];
	int n = 0;

	std::fstream plik;
	plik.open(nameOfFile, std::ios::in);
	int temp1;
	int temp2;

	if (!plik.good())
	{
		std::cout << "Plik nie istnieje";
		PlayGameWindow.close();
	}

	for (n = 0; n < blocks; n++)
	{
		plik >> temp1;
		plik >> temp2;
		block[n].setPos(temp1, temp2);

	}
	plik.close();
	
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
					WhichKeyIsPressed = 5;
					break;
				}
				case 2:
				{
					PlayGameWindow.clear();
					loadHelpScreen.draw(PlayGameWindow);
					PlayGameWindow.display();
					WhichKeyIsPressed = 5;
					break;
				}
				case 0:
				{
					loadGameOverScreen.draw(PlayGameWindow);
					PlayGameWindow.display();
					break;
				}
				case 3:
				{
					loadNextLevelScreen.draw(PlayGameWindow);
					PlayGameWindow.display();
					break;
				}

			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				PlayGameWindow.close();
			}


			if ((WhichKeyIsPressed == 1 || WhichKeyIsPressed == 2 || WhichKeyIsPressed == 5) && event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Backspace)
			{
				wait = true;
			}

			if (WhichKeyIsPressed == 3 && event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Enter)
			{
				PlayGameWindow.close();
				//Level2 start;
			}
		}
		else {
			if (p1.getPos().x > (PlayGameWindow.getSize().x) - radiusWithOutline || p1.getPos().x < 4) dx = -dx;
			if (p1.getPos().y > (PlayGameWindow.getSize().y) - radiusWithOutline || p1.getPos().y < 4) dy = -dy;
			if ((p1.getPos().x > pal1.getPos().x) && (p1.getPos().x < ((pal1.getPos().x) + pal1.getSize().x)) && (p1.getPos().y > pal1.getPos().y - (p1.getRadius()*2)) && (p1.getPos().y < (pal1.getPos().y) + pal1.getSize().y))
				dy = -(rand() % 3 + 4);
			if (p1.getPos().y + radiusWithOutline > pal1.getPos().y + pal1.getSize().y+5) { wait = !wait; WhichKeyIsPressed = 0; }

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

			/*sf::Vector2i localPosition = sf::Mouse::getPosition(PlayGameWindow);
			pal1.setPos(localPosition.x, 560);*/
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) { pal1.przesun(-15.f, 0.f); }
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) { pal1.przesun(15.f, 0.f); }
			if (pal1.getPos().x < 0) { pal1.setPos(0, 560); }
			if (pal1.getPos().x > 680) { pal1.setPos(680, 560); }


			if (score == MAX_POINTS_IN_ROUND)
			{
				wait = !wait;
				event.key.code = sf::Keyboard::Q;
				WhichKeyIsPressed = 3;

			}


			PlayGameWindow.clear();
			PlayGameWindow.draw(p1.getPilka());
			PlayGameWindow.draw(pal1.getPaletka());
			PlayGameWindow.draw(scores);

			for (int k = 0; k < n; k++)
				PlayGameWindow.draw(block[k].getBlok());

			PlayGameWindow.display();
			if (TimeFlag == 0) { Sleep(1500); TimeFlag = 1; }
		}
	}
	SetTestScores(score);
}
//Level2::Level2()
//{
//	sf::ContextSettings settings;
//	sf::RenderWindow PlayGameWindow(sf::VideoMode(800, 600), "SFML works!", sf::Style::Default, settings);
//	PlayGameWindow.setFramerateLimit(60);
//
//	pilka p1(400, 300);
//	paletka pal1(300, 300, 120, 5);
//	int x = 0, y = 0;
//	int dx = 7, dy = 5;
//	int score = 0;
//	int WhichKeyIsPressed = 0;
//	bool wait = true;
//	int TimeFlag = 0;
//	std::string str = std::to_string(score);
//	int radiusWithOutline = 2 * ((p1.getPilka().getRadius()) + (p1.getPilka().getOutlineThickness()));
//	sf::Font font;
//	if (!font.loadFromFile("RetroGaming.ttf"))
//	{
//		std::cout << "wystapil blad podczas wczytywania czcionki" << std::endl;
//	}
//	sf::Text scores;
//	scores.setFont(font);
//	scores.setFillColor(sf::Color::White);
//	scores.setString(str);
//	scores.setPosition(20, 20);
//	scores.setCharacterSize(20);
//
//
//	PauseScreen loadPauseScreen(PlayGameWindow);
//	HelpScreen loadHelpScreen(PlayGameWindow);
//	GameOverScreen loadGameOverScreen(PlayGameWindow);
//	NextLevelScreen loadNextLevelScreen(PlayGameWindow);
//
//
//	blok block[100];
//	int n = 0;
//	for (int i = 1; i <= 8; i++)
//		for (int j = 1; j <= 8; j++)
//		{
//			block[n].setPos(i * 50 + 120, j * 26);
//			n++;
//		}
//
//	while (PlayGameWindow.isOpen())
//	{
//		sf::Event event;
//		while (PlayGameWindow.pollEvent(event))
//		{
//			if (event.type == sf::Event::Closed)
//				PlayGameWindow.close();
//			else
//				if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Escape)
//				{
//					wait = !wait;
//					event.key.code = sf::Keyboard::Q;
//					WhichKeyIsPressed = 1;
//				}
//			if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::F1)
//			{
//				wait = !wait;
//				event.key.code = sf::Keyboard::Q;
//				WhichKeyIsPressed = 2;
//			}
//
//		}
//		if (!wait)
//		{
//			switch (WhichKeyIsPressed)
//			{
//			case 1:
//			{
//
//				loadPauseScreen.draw(PlayGameWindow);
//				PlayGameWindow.display();
//				WhichKeyIsPressed = 5;
//				break;
//			}
//			case 2:
//			{
//				PlayGameWindow.clear();
//				loadHelpScreen.draw(PlayGameWindow);
//				PlayGameWindow.display();
//				WhichKeyIsPressed = 5;
//				break;
//			}
//			case 0:
//			{
//				loadGameOverScreen.draw(PlayGameWindow);
//				PlayGameWindow.display();
//				break;
//			}
//			case 3:
//			{
//				loadNextLevelScreen.draw(PlayGameWindow);
//				PlayGameWindow.display();
//				break;
//			}
//
//			}
//
//			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
//			{
//				PlayGameWindow.close();
//			}
//
//
//			if ((WhichKeyIsPressed == 1 || WhichKeyIsPressed == 2 || WhichKeyIsPressed == 5) && event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Backspace)
//			{
//				wait = true;
//			}
//
//			if (WhichKeyIsPressed == 3 && event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Enter)
//			{
//				PlayGameWindow.close();
//				Level3 start;
//			}
//		}
//		else {
//			if (p1.getPos().x > (PlayGameWindow.getSize().x) - radiusWithOutline || p1.getPos().x < 4) dx = -dx;
//			if (p1.getPos().y > (PlayGameWindow.getSize().y) - radiusWithOutline || p1.getPos().y < 4) dy = -dy;
//			if ((p1.getPos().x > pal1.getPos().x) && (p1.getPos().x < ((pal1.getPos().x) + pal1.getSize().x)) && (p1.getPos().y > pal1.getPos().y - (p1.getRadius() * 2)) && (p1.getPos().y < (pal1.getPos().y) + pal1.getSize().y))
//				dy = -(rand() % 3 + 4);
//			if (p1.getPos().y + radiusWithOutline > pal1.getPos().y + pal1.getSize().y + 5) { wait = !wait; WhichKeyIsPressed = 0; }
//
//			p1.przesun(dx, 0);
//			for (int i = 0; i < n; i++)
//				if (isCollide(p1, block[i]))
//				{
//					block[i].setPos(-100, 0);
//					dx = -dx;
//					score++;
//					std::string str = std::to_string(score);
//					scores.setString(str);
//					std::cout << "score: " << score << std::endl;
//
//				}
//
//			p1.przesun(0, dy);
//			for (int i = 0; i < n; i++)
//				if (isCollide(p1, block[i]))
//				{
//					block[i].setPos(-100, 0);
//					dy = -dy;
//					score++;
//					std::string str = std::to_string(score);
//					scores.setString(str);
//					std::cout << "score: " << score << std::endl;
//				}
//
//			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) { pal1.przesun(-15.f, 0.f); }
//			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) { pal1.przesun(15.f, 0.f); }
//
//
//			if (score == MAX_POINTS_IN_ROUND)
//			{
//				wait = !wait;
//				event.key.code = sf::Keyboard::Q;
//				WhichKeyIsPressed = 3;
//
//			}
//
//
//			PlayGameWindow.clear();
//			PlayGameWindow.draw(p1.getPilka());
//			PlayGameWindow.draw(pal1.getPaletka());
//			PlayGameWindow.draw(scores);
//
//			for (int k = 0; k < n; k++)
//				PlayGameWindow.draw(block[k].getBlok());
//
//			PlayGameWindow.display();
//			if (TimeFlag == 0) { Sleep(1500); TimeFlag = 1; }
//		}
//	}
//}
//Level3::Level3()
//{
//	sf::ContextSettings settings;
//	sf::RenderWindow PlayGameWindow(sf::VideoMode(800, 600), "SFML works!", sf::Style::Default, settings);
//	PlayGameWindow.setFramerateLimit(60);
//
//	pilka p1(400, 300);
//	paletka pal1(300, 300, 120, 5);
//	int x = 0, y = 0;
//	int dx = 7, dy = 5;
//	int score = 0;
//	int WhichKeyIsPressed = 0;
//	bool wait = true;
//	int TimeFlag = 0;
//	std::string str = std::to_string(score);
//	int radiusWithOutline = 2 * ((p1.getPilka().getRadius()) + (p1.getPilka().getOutlineThickness()));
//	sf::Font font;
//	if (!font.loadFromFile("RetroGaming.ttf"))
//	{
//		std::cout << "wystapil blad podczas wczytywania czcionki" << std::endl;
//	}
//	sf::Text scores;
//	scores.setFont(font);
//	scores.setFillColor(sf::Color::White);
//	scores.setString(str);
//	scores.setPosition(20, 20);
//	scores.setCharacterSize(20);
//
//
//	PauseScreen loadPauseScreen(PlayGameWindow);
//	HelpScreen loadHelpScreen(PlayGameWindow);
//	GameOverScreen loadGameOverScreen(PlayGameWindow);
//	NextLevelScreen loadNextLevelScreen(PlayGameWindow);
//
//
//	blok block[100];
//	int n = 0;
//	for (int i = 1; i <= 6; i++)
//		for (int j = 1; j <= 6; j++)
//		{
//			block[n].setPos(i * 50 + 120, j * 26);
//			n++;
//		}
//
//	while (PlayGameWindow.isOpen())
//	{
//		sf::Event event;
//		while (PlayGameWindow.pollEvent(event))
//		{
//			if (event.type == sf::Event::Closed)
//				PlayGameWindow.close();
//			else
//				if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Escape)
//				{
//					wait = !wait;
//					event.key.code = sf::Keyboard::Q;
//					WhichKeyIsPressed = 1;
//				}
//			if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::F1)
//			{
//				wait = !wait;
//				event.key.code = sf::Keyboard::Q;
//				WhichKeyIsPressed = 2;
//			}
//
//		}
//		if (!wait)
//		{
//			switch (WhichKeyIsPressed)
//			{
//			case 1:
//			{
//
//				loadPauseScreen.draw(PlayGameWindow);
//				PlayGameWindow.display();
//				WhichKeyIsPressed = 5;
//				break;
//			}
//			case 2:
//			{
//				PlayGameWindow.clear();
//				loadHelpScreen.draw(PlayGameWindow);
//				PlayGameWindow.display();
//				WhichKeyIsPressed = 5;
//				break;
//			}
//			case 0:
//			{
//				loadGameOverScreen.draw(PlayGameWindow);
//				PlayGameWindow.display();
//				break;
//			}
//			case 3:
//			{
//				loadNextLevelScreen.draw(PlayGameWindow);
//				PlayGameWindow.display();
//				break;
//			}
//
//			}
//
//			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
//			{
//				PlayGameWindow.close();
//			}
//
//
//			if ((WhichKeyIsPressed == 1 || WhichKeyIsPressed == 2 || WhichKeyIsPressed == 5) && event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Backspace)
//			{
//				wait = true;
//			}
//
//			if (WhichKeyIsPressed == 3 && event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Enter)
//			{
//				PlayGameWindow.close();
//				Level4 start;
//			}
//		}
//		else {
//			if (p1.getPos().x > (PlayGameWindow.getSize().x) - radiusWithOutline || p1.getPos().x < 4) dx = -dx;
//			if (p1.getPos().y > (PlayGameWindow.getSize().y) - radiusWithOutline || p1.getPos().y < 4) dy = -dy;
//			if ((p1.getPos().x > pal1.getPos().x) && (p1.getPos().x < ((pal1.getPos().x) + pal1.getSize().x)) && (p1.getPos().y > pal1.getPos().y - (p1.getRadius() * 2)) && (p1.getPos().y < (pal1.getPos().y) + pal1.getSize().y))
//				dy = -(rand() % 3 + 4);
//			if (p1.getPos().y + radiusWithOutline > pal1.getPos().y + pal1.getSize().y + 5) { wait = !wait; WhichKeyIsPressed = 0; }
//
//			p1.przesun(dx, 0);
//			for (int i = 0; i < n; i++)
//				if (isCollide(p1, block[i]))
//				{
//					block[i].setPos(-100, 0);
//					dx = -dx;
//					score++;
//					std::string str = std::to_string(score);
//					scores.setString(str);
//					std::cout << "score: " << score << std::endl;
//
//				}
//
//			p1.przesun(0, dy);
//			for (int i = 0; i < n; i++)
//				if (isCollide(p1, block[i]))
//				{
//					block[i].setPos(-100, 0);
//					dy = -dy;
//					score++;
//					std::string str = std::to_string(score);
//					scores.setString(str);
//					std::cout << "score: " << score << std::endl;
//				}
//
//			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) { pal1.przesun(-15.f, 0.f); }
//			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) { pal1.przesun(15.f, 0.f); }
//
//
//			if (score == MAX_POINTS_IN_ROUND)
//			{
//				wait = !wait;
//				event.key.code = sf::Keyboard::Q;
//				WhichKeyIsPressed = 3;
//
//			}
//
//
//			PlayGameWindow.clear();
//			PlayGameWindow.draw(p1.getPilka());
//			PlayGameWindow.draw(pal1.getPaletka());
//			PlayGameWindow.draw(scores);
//
//			for (int k = 0; k < n; k++)
//				PlayGameWindow.draw(block[k].getBlok());
//
//			PlayGameWindow.display();
//			if (TimeFlag == 0) { Sleep(1500); TimeFlag = 1; }
//		}
//	}
//}
//Level4::Level4()
//{
//	sf::ContextSettings settings;
//	sf::RenderWindow PlayGameWindow(sf::VideoMode(800, 600), "SFML works!", sf::Style::Default, settings);
//	PlayGameWindow.setFramerateLimit(60);
//
//	pilka p1(400, 300);
//	paletka pal1(300, 300, 120, 5);
//	int x = 0, y = 0;
//	int dx = 7, dy = 5;
//	int score = 0;
//	int WhichKeyIsPressed = 0;
//	bool wait = true;
//	int TimeFlag = 0;
//	std::string str = std::to_string(score);
//	int radiusWithOutline = 2 * ((p1.getPilka().getRadius()) + (p1.getPilka().getOutlineThickness()));
//	sf::Font font;
//	if (!font.loadFromFile("RetroGaming.ttf"))
//	{
//		std::cout << "wystapil blad podczas wczytywania czcionki" << std::endl;
//	}
//	sf::Text scores;
//	scores.setFont(font);
//	scores.setFillColor(sf::Color::White);
//	scores.setString(str);
//	scores.setPosition(20, 20);
//	scores.setCharacterSize(20);
//
//
//	PauseScreen loadPauseScreen(PlayGameWindow);
//	HelpScreen loadHelpScreen(PlayGameWindow);
//	GameOverScreen loadGameOverScreen(PlayGameWindow);
//	NextLevelScreen loadNextLevelScreen(PlayGameWindow);
//
//
//	blok block[100];
//	int n = 0;
//	for (int i = 1; i <= 4; i++)
//		for (int j = 1; j <= 4; j++)
//		{
//			block[n].setPos(i * 50 + 120, j * 26);
//			n++;
//		}
//
//	while (PlayGameWindow.isOpen())
//	{
//		sf::Event event;
//		while (PlayGameWindow.pollEvent(event))
//		{
//			if (event.type == sf::Event::Closed)
//				PlayGameWindow.close();
//			else
//				if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Escape)
//				{
//					wait = !wait;
//					event.key.code = sf::Keyboard::Q;
//					WhichKeyIsPressed = 1;
//				}
//			if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::F1)
//			{
//				wait = !wait;
//				event.key.code = sf::Keyboard::Q;
//				WhichKeyIsPressed = 2;
//			}
//
//		}
//		if (!wait)
//		{
//			switch (WhichKeyIsPressed)
//			{
//			case 1:
//			{
//
//				loadPauseScreen.draw(PlayGameWindow);
//				PlayGameWindow.display();
//				WhichKeyIsPressed = 5;
//				break;
//			}
//			case 2:
//			{
//				PlayGameWindow.clear();
//				loadHelpScreen.draw(PlayGameWindow);
//				PlayGameWindow.display();
//				WhichKeyIsPressed = 5;
//				break;
//			}
//			case 0:
//			{
//				loadGameOverScreen.draw(PlayGameWindow);
//				PlayGameWindow.display();
//				break;
//			}
//			case 3:
//			{
//				loadNextLevelScreen.draw(PlayGameWindow);
//				PlayGameWindow.display();
//				break;
//			}
//
//			}
//
//			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
//			{
//				PlayGameWindow.close();
//			}
//
//
//			if ((WhichKeyIsPressed == 1 || WhichKeyIsPressed == 2 || WhichKeyIsPressed == 5) && event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Backspace)
//			{
//				wait = true;
//			}
//
//			if (WhichKeyIsPressed == 3 && event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Enter)
//			{
//				PlayGameWindow.close();
//				Level5 start;
//			}
//		}
//		else {
//			if (p1.getPos().x > (PlayGameWindow.getSize().x) - radiusWithOutline || p1.getPos().x < 4) dx = -dx;
//			if (p1.getPos().y > (PlayGameWindow.getSize().y) - radiusWithOutline || p1.getPos().y < 4) dy = -dy;
//			if ((p1.getPos().x > pal1.getPos().x) && (p1.getPos().x < ((pal1.getPos().x) + pal1.getSize().x)) && (p1.getPos().y > pal1.getPos().y - (p1.getRadius() * 2)) && (p1.getPos().y < (pal1.getPos().y) + pal1.getSize().y))
//				dy = -(rand() % 3 + 4);
//			if (p1.getPos().y + radiusWithOutline > pal1.getPos().y + pal1.getSize().y + 5) { wait = !wait; WhichKeyIsPressed = 0; }
//
//			p1.przesun(dx, 0);
//			for (int i = 0; i < n; i++)
//				if (isCollide(p1, block[i]))
//				{
//					block[i].setPos(-100, 0);
//					dx = -dx;
//					score++;
//					std::string str = std::to_string(score);
//					scores.setString(str);
//					std::cout << "score: " << score << std::endl;
//
//				}
//
//			p1.przesun(0, dy);
//			for (int i = 0; i < n; i++)
//				if (isCollide(p1, block[i]))
//				{
//					block[i].setPos(-100, 0);
//					dy = -dy;
//					score++;
//					std::string str = std::to_string(score);
//					scores.setString(str);
//					std::cout << "score: " << score << std::endl;
//				}
//
//			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) { pal1.przesun(-15.f, 0.f); }
//			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) { pal1.przesun(15.f, 0.f); }
//
//
//			if (score == MAX_POINTS_IN_ROUND)
//			{
//				wait = !wait;
//				event.key.code = sf::Keyboard::Q;
//				WhichKeyIsPressed = 3;
//
//			}
//
//
//			PlayGameWindow.clear();
//			PlayGameWindow.draw(p1.getPilka());
//			PlayGameWindow.draw(pal1.getPaletka());
//			PlayGameWindow.draw(scores);
//
//			for (int k = 0; k < n; k++)
//				PlayGameWindow.draw(block[k].getBlok());
//
//			PlayGameWindow.display();
//			if (TimeFlag == 0) { Sleep(1500); TimeFlag = 1; }
//		}
//	}
//}
//Level5::Level5()
//{
//	sf::ContextSettings settings;
//	sf::RenderWindow PlayGameWindow(sf::VideoMode(800, 600), "SFML works!", sf::Style::Default, settings);
//	PlayGameWindow.setFramerateLimit(60);
//
//	pilka p1(400, 300);
//	paletka pal1(300, 300, 120, 5);
//	int x = 0, y = 0;
//	int dx = 7, dy = 5;
//	int score = 0;
//	int WhichKeyIsPressed = 0;
//	bool wait = true;
//	int TimeFlag = 0;
//	std::string str = std::to_string(score);
//	int radiusWithOutline = 2 * ((p1.getPilka().getRadius()) + (p1.getPilka().getOutlineThickness()));
//	sf::Font font;
//	if (!font.loadFromFile("RetroGaming.ttf"))
//	{
//		std::cout << "wystapil blad podczas wczytywania czcionki" << std::endl;
//	}
//	sf::Text scores;
//	scores.setFont(font);
//	scores.setFillColor(sf::Color::White);
//	scores.setString(str);
//	scores.setPosition(20, 20);
//	scores.setCharacterSize(20);
//
//
//	PauseScreen loadPauseScreen(PlayGameWindow);
//	HelpScreen loadHelpScreen(PlayGameWindow);
//	GameOverScreen loadGameOverScreen(PlayGameWindow);
//	NextLevelScreen loadNextLevelScreen(PlayGameWindow);
//
//
//	blok block[100];
//	int n = 0;
//	//for (int i = 1; i <= 2; i++)
//	//	for (int j = 1; j <= 2; j++)
//	//	{
//	//		block[n].setPos(i * 50 + 120, j * 26);
//	//		n++;
//	//	}
//
//	std::fstream plik;
//	plik.open("dane.txt", std::ios::in);
//	int temp1;
//	int temp2;
//
//	if (plik.good() == false)
//	{
//		std::cout << "Plik nie istnieje";
//		PlayGameWindow.close();
//	}
//	//while (!plik.eof())
//	for (n = 0; n < 4; n++)
//	{
//		//getline(plik, linia);
//		//temp = atoi(linia.c_str());
//		//cout << linia << endl;
//		plik >> temp1;
//		plik >> temp2;
//		block[n].setPos(temp1, temp2);
//
//	}
//
//	plik.close();
//
//	while (PlayGameWindow.isOpen())
//	{
//		sf::Event event;
//		while (PlayGameWindow.pollEvent(event))
//		{
//			if (event.type == sf::Event::Closed)
//				PlayGameWindow.close();
//			else
//				if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Escape)
//				{
//					wait = !wait;
//					event.key.code = sf::Keyboard::Q;
//					WhichKeyIsPressed = 1;
//				}
//			if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::F1)
//			{
//				wait = !wait;
//				event.key.code = sf::Keyboard::Q;
//				WhichKeyIsPressed = 2;
//			}
//
//		}
//		if (!wait)
//		{
//			switch (WhichKeyIsPressed)
//			{
//			case 1:
//			{
//
//				loadPauseScreen.draw(PlayGameWindow);
//				PlayGameWindow.display();
//				WhichKeyIsPressed = 5;
//				break;
//			}
//			case 2:
//			{
//				PlayGameWindow.clear();
//				loadHelpScreen.draw(PlayGameWindow);
//				PlayGameWindow.display();
//				WhichKeyIsPressed = 5;
//				break;
//			}
//			case 0:
//			{
//				loadGameOverScreen.draw(PlayGameWindow);
//				PlayGameWindow.display();
//				break;
//			}
//			case 3:
//			{
//				loadNextLevelScreen.draw(PlayGameWindow);
//				PlayGameWindow.display();
//				break;
//			}
//
//			}
//
//			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
//			{
//				PlayGameWindow.close();
//			}
//
//
//			if ((WhichKeyIsPressed == 1 || WhichKeyIsPressed == 2 || WhichKeyIsPressed == 5) && event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Backspace)
//			{
//				wait = true;
//			}
//
//			if (WhichKeyIsPressed == 3 && event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Enter)
//			{
//				PlayGameWindow.close();
//				std::cout << "PRZESZEDLES WSZYSTKIE POZIOMY GRY" << std::endl;
//			}
//		}
//		else {
//			if (p1.getPos().x > (PlayGameWindow.getSize().x) - radiusWithOutline || p1.getPos().x < 4) dx = -dx;
//			if (p1.getPos().y > (PlayGameWindow.getSize().y) - radiusWithOutline || p1.getPos().y < 4) dy = -dy;
//			if ((p1.getPos().x > pal1.getPos().x) && (p1.getPos().x < ((pal1.getPos().x) + pal1.getSize().x)) && (p1.getPos().y > pal1.getPos().y - (p1.getRadius() * 2)) && (p1.getPos().y < (pal1.getPos().y) + pal1.getSize().y))
//				dy = -(rand() % 3 + 4);
//			if (p1.getPos().y + radiusWithOutline > pal1.getPos().y + pal1.getSize().y + 5) { wait = !wait; WhichKeyIsPressed = 0; }
//
//			p1.przesun(dx, 0);
//			for (int i = 0; i < n; i++)
//				if (isCollide(p1, block[i]))
//				{
//					block[i].setPos(-100, 0);
//					dx = -dx;
//					score++;
//					std::string str = std::to_string(score);
//					scores.setString(str);
//					std::cout << "score: " << score << std::endl;
//
//				}
//
//			p1.przesun(0, dy);
//			for (int i = 0; i < n; i++)
//				if (isCollide(p1, block[i]))
//				{
//					block[i].setPos(-100, 0);
//					dy = -dy;
//					score++;
//					std::string str = std::to_string(score);
//					scores.setString(str);
//					std::cout << "score: " << score << std::endl;
//				}
//
//			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) { pal1.przesun(-15.f, 0.f); }
//			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) { pal1.przesun(15.f, 0.f); }
//
//
//			if (score == MAX_POINTS_IN_ROUND)
//			{
//				wait = !wait;
//				event.key.code = sf::Keyboard::Q;
//				WhichKeyIsPressed = 3;
//
//			}
//
//
//			PlayGameWindow.clear();
//			PlayGameWindow.draw(p1.getPilka());
//			PlayGameWindow.draw(pal1.getPaletka());
//			PlayGameWindow.draw(scores);
//
//			for (int k = 0; k < n; k++)
//				PlayGameWindow.draw(block[k].getBlok());
//
//			PlayGameWindow.display();
//			if (TimeFlag == 0) { Sleep(1500); TimeFlag = 1; }
//		}
//	}
//}
