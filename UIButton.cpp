#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <functional> 
#include <iostream> 
#include "UIButton.h"
#include "GameEvents.h"
#include "InputEvents.h"
#include "GameObject.h"
#include "Window.h"
#include "UIHelper.h"

using namespace std;
using namespace sf;

UIButton::UIButton(Vector2f position, Vector2f size, string _text, Color color) {
	GetBody().setSize(size);
	GetBody().setOrigin(GetBody().getSize() / 2.0f);
	GetBody().setPosition(position);
	GetBody().setFillColor(color);

	text.setPosition(GetBody().getOrigin());
	text.setFillColor(Color::White);
	text.setScale(size);
	text.setCharacterSize(32);
	text.setFont(GetFont());

	MouseDownEvent[Id] = [this](auto mouseButton, auto mousePosition) { OnMouseDown(mouseButton, mousePosition); };

	AddDrawable(GetBody(), 0);
	AddDrawable(text, 0);
}

UIButton::~UIButton() {
	OnClickedEvent.clear();
	MouseDownEvent.erase(Id);

	RemoveDrawable(GetBody(), 0);
	RemoveDrawable(text, 0);
}

void UIButton::OnMouseDown(Mouse::Button mouseButton, Vector2i mousePosition) {
	if (mouseButton != Mouse::Button::Left) { return; }
	if (!GetBody().getGlobalBounds().contains((Vector2f)mousePosition)) { return; }

	for (auto const& e : OnClickedEvent) {
		e.second();
	}
}
