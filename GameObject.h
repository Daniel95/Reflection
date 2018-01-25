#pragma once

#include <SFML/Graphics.hpp>
#include "Tags.h"

using namespace sf;

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

