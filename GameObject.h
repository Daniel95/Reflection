#pragma once

#include <SFML/Graphics.hpp>
#include "Tags.h"

using namespace sf;

//GameObjects are used by all visible elements in the game
//They have an Body, and Id and a tag
//Each Id is unique, tags are used to categorize different types of GameObjects (See Tags.h)
class GameObject {
private:
	bool destroying = false;
	RectangleShape body;
public:
	std::string Id = "";
	Tags::Tag Tag;

	GameObject();
	virtual ~GameObject();
	void Destroy();
	RectangleShape& GetBody() {
		return body;
	};
};

