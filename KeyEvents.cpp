#include "stdafx.h"
#include "KeyEvents.h"

vector<function<void(Keyboard::Key)>> KeyDownEvent;
vector<function<void(Keyboard::Key)>> KeyEvent;
vector<function<void(Keyboard::Key)>> KeyUpEvent;
vector<Keyboard::Key> pressedKeys;

void HandleInputEvents(Event sfEvent) {
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
			KeyUpEvent[i](sfEvent.key.code);
		}
		pressedKeys.erase(remove(pressedKeys.begin(), pressedKeys.end(), pressedKey), pressedKeys.end());
		break;
	}
}

void HandleInputUpdate() {
	for (size_t i = 0; i < pressedKeys.size(); i++) {
		for (size_t e = 0; e < KeyDownEvent.size(); e++) {
			KeyEvent[e](pressedKeys[i]);
		}
	}
}