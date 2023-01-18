#pragma once
#include <SFML/Graphics.hpp>
#include "pilka.h"
#include "blok.h"

bool isCollide(pilka s1, blok s2);
void SaveToFile(int allScores);

class Level1
{
private:
	int testScores = 0;
public:
	void RunLevel(std::string nameOfFile, int blocks, Level1 tablica[], int paletkaWidth);
	void SetTestScores(int scores) { testScores = scores; };
	void RunNextLevel(int level, int nextLevel, Level1 tablica[]);
	int GetTestScores() { return testScores; }
};