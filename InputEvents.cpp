#include "stdafx.h"
#include "InputEvents.h"
#include <iostream>

vector<function<void(Keyboard::Key)>> KeyDownEvent;
vector<function<void(Keyboard::Key)>> KeyEvent;
vector<function<void(Keyboard::Key)>> KeyUpEvent;

//Parameters: MouseButton, Pos, Delta
vector<function<void(Mouse::Button, Vector2i)>> MouseDownEvent;
vector<function<void(Mouse::Button, Vector2i, Vector2i)>> MouseEvent;
vector<function<void(Mouse::Button, Vector2i)>> MouseUpEvent;

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
			for (size_t i = 0; i < KeyDownEvent.size(); i++) {
				KeyDownEvent[i](pressedKey);
			}
			pressedKeys.push_back(pressedKey);
		}
		break;
	case Event::KeyReleased:
		for (size_t i = 0; i < KeyUpEvent.size(); i++) {
			KeyUpEvent[i](pressedKey);
		}
		pressedKeys.erase(remove(pressedKeys.begin(), pressedKeys.end(), pressedKey), pressedKeys.end());
		break;
	}
}

static void HandleMouseEvents(Event sfEvent) {
	Mouse::Button pressedMouseButton = sfEvent.mouseButton.button;
	Vector2i mousePosition = Mouse::getPosition();

	switch (sfEvent.type) {
	case Event::MouseButtonPressed:
		if (std::find(pressedMouseButtons.begin(), pressedMouseButtons.end(), pressedMouseButton) == pressedMouseButtons.end()) {
			for (size_t i = 0; i < MouseDownEvent.size(); i++) {
				MouseDownEvent[i](pressedMouseButton, mousePosition);
			}
			pressedMouseButtons.push_back(pressedMouseButton);
		}
		break;
	case Event::MouseButtonReleased:
		for (size_t i = 0; i < MouseUpEvent.size(); i++) {
			MouseUpEvent[i](pressedMouseButton, mousePosition);
		}
		pressedMouseButtons.erase(remove(pressedMouseButtons.begin(), pressedMouseButtons.end(), pressedMouseButton), pressedMouseButtons.end());
		break;
	}
}

void HandleInputUpdate() {
	for (size_t i = 0; i < pressedKeys.size(); i++) {
		for (size_t e = 0; e < KeyEvent.size(); e++) {
			KeyEvent[e](pressedKeys[i]);
		}
	}
	
	Vector2i mousePosition = Mouse::getPosition();
	mouseDelta = mousePosition - previousMousePosition;
	previousMousePosition = mousePosition;

	for (size_t i = 0; i < pressedMouseButtons.size(); i++) {
		for (size_t e = 0; e < MouseEvent.size(); e++) {
			MouseEvent[e](pressedMouseButtons[i], mousePosition, mouseDelta);
		}
	}
}