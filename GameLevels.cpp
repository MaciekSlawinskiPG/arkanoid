#define _CRT_SECURE_NO_WARNINGS
#include <time.h>
#include <conio.h>
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

#define MAX_POINTS_IN_ROUND 2

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
void SaveToFile(int allScores)
{
	time_t czas;
	struct tm* data;
	char godzina[80];

	time(&czas);
	data = localtime(&czas);

	strftime(godzina, 80, "%H:%M:%S", data);

	std::fstream file;
	file.open("PreviousScores.txt", std::ios::app);
	file << godzina << "        " << allScores << std::endl;
	file.close();
}
//void Level1::SetTestScores(int scores)
//{
//	testScores = scores;
//}

void Level1::RunLevel(std::string nameOfFile, int blocks, Level1 tablica[], int paletkaWidth)
{
	int levelID = 0;
	switch (blocks)
	{
	case 100: {levelID = 1; break; }
	case 64: {levelID = 2; break; }
	case 36: {levelID = 3; break; }
	case 16: {levelID = 4; break; }
	case 6: {levelID = 5; break; }
	}



	sf::ContextSettings settings;
	sf::RenderWindow PlayGameWindow(sf::VideoMode(800, 600), "SFML works!", sf::Style::Default, settings);
	PlayGameWindow.setFramerateLimit(60);

	sf::Texture texture;
	texture.loadFromFile("background.jpg");
	sf::Sprite backgroundImage;
	backgroundImage.setTexture(texture);

	pilka p1(400, 300);
	paletka pal1(300, 300, paletkaWidth, 5);
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
				case 1: // Pause Game (ESC)
				{
					PlayGameWindow.draw(backgroundImage);
					PlayGameWindow.draw(scores);
					PlayGameWindow.draw(p1.getPilka());
					PlayGameWindow.draw(pal1.getPaletka());

					for (int k = 0; k < n; k++) PlayGameWindow.draw(block[k].getBlok());
					loadPauseScreen.draw(PlayGameWindow);
					PlayGameWindow.display();
					WhichKeyIsPressed = 5;
					break;
				}
				case 2: // Help Screen (F1)
				{
					PlayGameWindow.clear();
					loadHelpScreen.draw(PlayGameWindow);
					PlayGameWindow.display();
					WhichKeyIsPressed = 5;
					break;
				}
				case 0: // Game Over
				{
					PlayGameWindow.draw(backgroundImage);
					PlayGameWindow.draw(scores);
					PlayGameWindow.draw(p1.getPilka());
					PlayGameWindow.draw(pal1.getPaletka());
					
					for (int k = 0; k < n; k++) PlayGameWindow.draw(block[k].getBlok());
					loadGameOverScreen.draw(PlayGameWindow);
					PlayGameWindow.display();
					
					break;
				}
				case 3: // Next level screen
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
				
				switch (levelID)
				{
				case 1: {std::cout << "Uruchamian Poziom 2..." << std::endl; tablica[1].RunLevel("blocksPositionLevel2.txt", 64, tablica, 200); break; }
				case 2: {std::cout << "Uruchamian Poziom 3..." << std::endl; tablica[2].RunLevel("blocksPositionLevel3.txt", 36, tablica, 200); break; }
				case 3: {std::cout << "Uruchamian Poziom 4..." << std::endl; tablica[3].RunLevel("blocksPositionLevel4.txt", 16, tablica, 200); break; }
				case 4: {std::cout << "Uruchamian Poziom 5..." << std::endl; tablica[4].RunLevel("blocksPositionLevel5.txt", 6, tablica, 200); break; }
				}
			}
		}
		else {
			if (p1.getPos().x > (PlayGameWindow.getSize().x) - radiusWithOutline || p1.getPos().x < 4) dx = -dx;
			if (p1.getPos().y > (PlayGameWindow.getSize().y) - radiusWithOutline || p1.getPos().y < 4) dy = -dy;
			if ((p1.getPos().x > pal1.getPos().x) && (p1.getPos().x < ((pal1.getPos().x) + pal1.getSize().x)) && (p1.getPos().y > pal1.getPos().y - (p1.getRadius()*2)) && (p1.getPos().y < (pal1.getPos().y) + pal1.getSize().y))
				dy = -(rand() % 3 + 4);
			if (p1.getPos().y + radiusWithOutline > pal1.getPos().y + pal1.getSize().y+5) 
			{ 
				wait = !wait; 
				WhichKeyIsPressed = 0; 
				tablica[levelID - 1].SetTestScores(score);
				std::cout << "- - - - -" << std::endl << "Level 1: " << tablica[0].GetTestScores() << std::endl << "Level 2: " << tablica[1].GetTestScores() << std::endl << "Level 3: " << tablica[2].GetTestScores() << std::endl << "Level 4: " << tablica[3].GetTestScores() << std::endl << "Level 5: " << tablica[4].GetTestScores() << std::endl << "- - - - -" << std::endl;
				std::cout << std::endl << std::endl << "- - - - -" << std::endl << "Laczna ilosc punktow to: " << tablica[0].GetTestScores() + tablica[1].GetTestScores() + tablica[2].GetTestScores() + tablica[3].GetTestScores() + tablica[4].GetTestScores();
				SaveToFile(tablica[0].GetTestScores() + tablica[1].GetTestScores() + tablica[2].GetTestScores() + tablica[3].GetTestScores() + tablica[4].GetTestScores());
			}

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

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) { pal1.przesun(-15.f, 0.f); }
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) { pal1.przesun(15.f, 0.f); }
			if (pal1.getPos().x < 0) { pal1.setPos(0, 560); }
			if (pal1.getPos().x > 800 - paletkaWidth) { pal1.setPos(800 - paletkaWidth, 560); }


			if (score == levelID)
			{
				PlayGameWindow.draw(scores);
				wait = !wait;
				event.key.code = sf::Keyboard::Q;
				WhichKeyIsPressed = 3;
				tablica[levelID-1].SetTestScores(score);
				if (levelID == 5)
				{
					std::cout << "- - - - -" << std::endl << "Level 1: " << tablica[0].GetTestScores() << std::endl << "Level 2: " << tablica[1].GetTestScores() << std::endl << "Level 3: " << tablica[2].GetTestScores() << std::endl << "Level 4: " << tablica[3].GetTestScores() << std::endl << "Level 5: " << tablica[4].GetTestScores() << std::endl << "- - - - -" << std::endl;
					std::cout << std::endl << std::endl << "- - - - -" << std::endl << "Laczna ilosc punktow to: " << tablica[0].GetTestScores() + tablica[1].GetTestScores() + tablica[2].GetTestScores() + tablica[3].GetTestScores() + tablica[4].GetTestScores() << std::endl;
				}

			}

			if (wait)
			{
				PlayGameWindow.clear();
				PlayGameWindow.draw(backgroundImage);
				PlayGameWindow.draw(p1.getPilka());
				PlayGameWindow.draw(pal1.getPaletka());
				PlayGameWindow.draw(scores);

				for (int k = 0; k < n; k++)
					PlayGameWindow.draw(block[k].getBlok());

				PlayGameWindow.display();
			}
			
			if (TimeFlag == 0) { Sleep(1500); TimeFlag = 1; }
		}
	}
	SetTestScores(score);
}
