#include "RankingScreen.h"
#include <iostream>
#include <fstream>

#define MAX_ITEMS 6

RankingScreen::RankingScreen(float width, float height)
{
	if (!font.loadFromFile("RetroGaming.ttf"))
	{
		std::cout << "wystapil blad podczas wczytywania czcionki" << std::endl;
	}


	std::fstream plik;
	plik.open("PreviousScores.txt", std::ios::in);
	int ileWierszy = 0;
	std::string temp;
	std::string linia[5];

	if (plik.good() == false) std::cout << "Plik nie istnieje";
	while (!plik.eof()) while (std::getline(plik, temp)) ++ileWierszy;
	plik.close();
	plik.open("PreviousScores.txt", std::ios::in);
	for (int i = 0; i < ileWierszy - 5; i++) std::getline(plik, temp);
	for (int i = 0; i < 5; i++) getline(plik, linia[i]);
	plik.close();


	std::string test = "Wynik1";
	menuItem[0].setFont(font);
	menuItem[0].setCharacterSize(22);
	menuItem[0].setFillColor(sf::Color::White);
	menuItem[0].setString(linia[0]);
	menuItem[0].setPosition(sf::Vector2f(300, height / (MAX_ITEMS + 1) * 1 - 20));

	menuItem[1].setFont(font);
	menuItem[1].setCharacterSize(22);
	menuItem[1].setFillColor(sf::Color::White);
	menuItem[1].setString(linia[1]);
	menuItem[1].setPosition(sf::Vector2f(300, height / (MAX_ITEMS + 1) * 2 - 20));

	menuItem[2].setFont(font);
	menuItem[2].setCharacterSize(22);
	menuItem[2].setFillColor(sf::Color::White);
	menuItem[2].setString(linia[2]);
	menuItem[2].setPosition(sf::Vector2f(300, height / (MAX_ITEMS + 1) * 3 - 20));

	menuItem[3].setFont(font);
	menuItem[3].setCharacterSize(22);
	menuItem[3].setFillColor(sf::Color::White);
	menuItem[3].setString(linia[3]);
	menuItem[3].setPosition(sf::Vector2f(300, height / (MAX_ITEMS + 1) * 4 - 20));

	menuItem[4].setFont(font);
	menuItem[4].setCharacterSize(22);
	menuItem[4].setFillColor(sf::Color::White);
	menuItem[4].setString(linia[4]);
	menuItem[4].setPosition(sf::Vector2f(300, height / (MAX_ITEMS + 1) * 5 - 20));

	menuItem[5].setFont(font);
	menuItem[5].setCharacterSize(37);
	menuItem[5].setFillColor(sf::Color::Red);
	menuItem[5].setString("      Wyjdz");
	menuItem[5].setPosition(sf::Vector2f(267, height / (MAX_ITEMS + 1) * 6 - 20));

}

void RankingScreen::draw(sf::RenderWindow& window)
{
	for (int i = 0; i < MAX_ITEMS; i++)
	{
		window.draw(menuItem[i]);
	}
}

void RankingScreen::RunRankingScreen()
{
	sf::ContextSettings settings;
	sf::RenderWindow RankingScreenWindow(sf::VideoMode(800, 600), "Arkanoid game", sf::Style::Default, settings);
	RankingScreenWindow.setFramerateLimit(60);

	sf::Texture texture;
	texture.loadFromFile("background.jpg");
	sf::Sprite backgroundImage;
	backgroundImage.setTexture(texture);

	RankingScreen window(RankingScreenWindow.getSize().x, RankingScreenWindow.getSize().y);

	while (RankingScreenWindow.isOpen())
	{
		sf::Event event;
		while (RankingScreenWindow.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				RankingScreenWindow.close();
				break;

			case sf::Event::KeyReleased:
				switch (event.key.code)
				{
				case sf::Keyboard::Enter:
					RankingScreenWindow.close();
					break;
				}
			}
		}
		RankingScreenWindow.clear();
		RankingScreenWindow.draw(backgroundImage);
		window.draw(RankingScreenWindow);
		RankingScreenWindow.display();

	}
}