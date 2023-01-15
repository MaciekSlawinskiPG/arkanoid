#include "Functions.h"
#include <SFML/Graphics.hpp>



int generateScoreCounter(sf::Font &font)
{
	int score = 0;
	std::string str = std::to_string(score);

	sf::Text scores;
	scores.setFont(font);
	scores.setFillColor(sf::Color::White);
	scores.setString(str);
	scores.setPosition(20, 20);
	scores.setCharacterSize(20);

	return score;
}