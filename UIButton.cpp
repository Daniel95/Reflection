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

UIButton::UIButton(Vector2f position, Vector2f size, string string, Color color) {
	GetBody().setSize(size);
	GetBody().setOrigin(GetBody().getSize() / 2.0f);
	GetBody().setPosition(position);
	GetBody().setFillColor(color);

	text.setPosition(GetBody().getPosition());
	text.setFillColor(Color::White);
	text.setCharacterSize(32);
	text.setScale(Vector2f(1, 1));
	text.setFont(GetFont());
	text.setString(string);
	text.setOrigin(text.getLocalBounds().left + text.getLocalBounds().width / 2.0f,
		text.getLocalBounds().top + text.getLocalBounds().height / 2.0f);

	MouseDownEvent[Id] = [this](auto mouseButton, auto mousePosition) { OnMouseDown(mouseButton, mousePosition); };

	AddDrawable(GetBody(), 1);
	AddDrawable(text, 0);
}

UIButton::~UIButton() {
	OnClickedEvent.clear();
	MouseDownEvent.erase(Id);

	RemoveDrawable(GetBody(), 1);
	RemoveDrawable(text, 0);
}

void UIButton::OnMouseDown(Mouse::Button mouseButton, Vector2i mousePosition) {
	if (mouseButton != Mouse::Button::Left) { return; }
	if (!GetBody().getGlobalBounds().contains((Vector2f)mousePosition)) { return; }

	for (auto const& e : OnClickedEvent) {
		e.second();
	}
}
