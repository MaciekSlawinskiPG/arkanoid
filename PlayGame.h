#pragma once
#include <SFML/Graphics.hpp>
#include "pilka.h"
#include "blok.h"

class PlayGame
{
public:
	PlayGame();
	bool isCollide(pilka s1, blok s2);

};