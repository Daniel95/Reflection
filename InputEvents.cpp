#include "stdafx.h"
#include "InputEvents.h"
#include "Window.h"
#include <iostream>

map<string, function<void(Keyboard::Key)>> KeyDownEvent;
map<string, function<void(Keyboard::Key)>> KeyEvent;
map<string, function<void(Keyboard::Key)>> KeyUpEvent;

//Parameters: MouseButton, Pos, Delta
map<string, function<void(Mouse::Button, Vector2i)>> MouseDownEvent;
map<string, function<void(Mouse::Button, Vector2i, Vector2i)>> MouseEvent;
map<string, function<void(Mouse::Button, Vector2i)>> MouseUpEvent;

vector<Keyboard::Key> pressedKeys;
vector<Mouse::Button> pressedMouseButtons;

Vector2i mouseDelta;
Vector2i previousMousePosition;

static void HandleKeyEvents(Event sfEvent);
static void HandleMouseEvents(Event sfEvent);

void HandleInputEvents(Event sfEvent) {
	if (sfEvent.type == Event::KeyPressed || sfEvent.type == Event::KeyReleased) {
		HandleKeyEvents(sfEvent);
	} else if (sfEvent.type == Event::MouseButtonPressed || sfEvent.type == Event::MouseButtonReleased) {
		HandleMouseEvents(sfEvent);
	}
}

static void HandleKeyEvents(Event sfEvent) {
	Keyboard::Key pressedKey = sfEvent.key.code;

	switch (sfEvent.type) {
	case Event::KeyPressed:
		if (std::find(pressedKeys.begin(), pressedKeys.end(), pressedKey) == pressedKeys.end()) {
			for (auto const& x : KeyDownEvent) {
				x.second(pressedKey);
			}
			pressedKeys.push_back(pressedKey);
		}
		break;
	case Event::KeyReleased:
		for (auto const& x : KeyUpEvent) {
			x.second(pressedKey);
		}
		pressedKeys.erase(remove(pressedKeys.begin(), pressedKeys.end(), pressedKey), pressedKeys.end());
		break;
	}
}

static void HandleMouseEvents(Event sfEvent) {
	Mouse::Button pressedMouseButton = sfEvent.mouseButton.button;
	Vector2i mousePosition = Mouse::getPosition(GameWindow);

	switch (sfEvent.type) {
	case Event::MouseButtonPressed:
		if (std::find(pressedMouseButtons.begin(), pressedMouseButtons.end(), pressedMouseButton) == pressedMouseButtons.end()) {
			for (auto const& x : MouseDownEvent) {
				x.second(pressedMouseButton, mousePosition);
			}
			pressedMouseButtons.push_back(pressedMouseButton);
		}
		break;
	case Event::MouseButtonReleased:
		for (auto const& x : MouseUpEvent) {
			x.second(pressedMouseButton, mousePosition);
		}
		pressedMouseButtons.erase(remove(pressedMouseButtons.begin(), pressedMouseButtons.end(), pressedMouseButton), pressedMouseButtons.end());
		break;
	}
}

void HandleInputUpdate() {
	for (size_t i = 0; i < pressedKeys.size(); i++) {
		for (auto const& x : KeyEvent) {
			x.second(pressedKeys[i]);
		}
	}
	
	Vector2i mousePosition = Mouse::getPosition(GameWindow);
	mouseDelta = mousePosition - previousMousePosition;
	previousMousePosition = mousePosition;

	for (size_t i = 0; i < pressedMouseButtons.size(); i++) {
		for (auto const& x : MouseEvent) {
			x.second(pressedMouseButtons[i], mousePosition, mouseDelta);
		}
	}
}