#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;

class LevelObject {
private:

public:
	RectangleShape Body;

	LevelObject();
	virtual ~LevelObject();
};

