#pragma once

#include <SFML/Graphics.hpp>
#include "Tags.h"

using namespace sf;

class GameObject {
private:
	bool destroying = false;
public:
	RectangleShape Body;
	std::string Id = "";
	Tags::Tag Tag;

	GameObject();
	virtual ~GameObject();
	void Destroy();
};

