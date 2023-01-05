#pragma once
#include <SFML/Graphics.hpp>
#include "pilka.h"
#include "blok.h"

class Level1
{
public:
	Level1();
	bool isCollide(pilka s1, blok s2);

};