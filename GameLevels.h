#pragma once
#include <SFML/Graphics.hpp>
#include "pilka.h"
#include "blok.h"

bool isCollide(pilka s1, blok s2);


class Level1
{
private:
	int testScores = 0;
public:
	void RunLevel(std::string nameOfFile, int blocks);
	void SetTestScores(int scores);
	int GetTestScores() { return testScores; }
};

//class Level2
//{
//public: Level2();
//};
//
//class Level3
//{
//public: Level3();
//};
//
//class Level4
//{
//public: Level4();
//};
//
//class Level5
//{
//public: Level5();
//};