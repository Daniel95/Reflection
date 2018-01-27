#pragma once

#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <functional> 
#include <string>
#include "GameObject.h"

using namespace std;
using namespace sf;

class UIButton : public GameObject {
	Text text;
public:
	map<string, function<void()>> OnClickedEvent;

	string GetTextString() {
		return text.getString();
	}
	void SetTextString(string string) {
		text.setString(string);
	}

	UIButton(Vector2f position, Vector2f size, string text, Color color);
	~UIButton();
	void OnMouseDown(Mouse::Button mouseButton, Vector2i mousePosition);
};

