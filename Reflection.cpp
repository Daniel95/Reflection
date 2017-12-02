// Reflection.cpp : Defines the entry point for the console application.

#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <functional> 
#include <vector> 
#include <iostream>

using namespace std;
using namespace sf;

//Events
static std::vector<std::function<void(Event)>> SFEvent;
static std::vector<std::function<void()>> UpdateEvent;
static std::vector<std::function<void(Keyboard::Key)>> KeyDownEvent;
static std::vector<std::function<void(Keyboard::Key)>> KeyEvent;
static std::vector<std::function<void(Keyboard::Key)>> KeyUpEvent;

static CircleShape player(100.f);
const float PLAYER_SPEED = 0.4f;

void HandleInputEvents(Event sfEvent);
void HandleInputUpdate();
void OnKeyDown(Keyboard::Key key);
void OnKey(Keyboard::Key key);
void OnKeyUp(Keyboard::Key key);

RenderWindow window(VideoMode(1280, 920), "Reflection", Style::Close | Style::Titlebar);

int main() {
	player.setFillColor(Color::Green);

	KeyDownEvent.push_back(OnKeyDown);
	KeyEvent.push_back(OnKey);
	KeyUpEvent.push_back(OnKeyUp);
	SFEvent.push_back(HandleInputEvents);
	UpdateEvent.push_back(HandleInputUpdate);

	while (window.isOpen()) {
		Event sfEvent;
		while (window.pollEvent(sfEvent)) {
			switch (sfEvent.type) {
				case Event::Closed:
					window.close();
					break;
			}

			for (size_t i = 0; i < SFEvent.size(); i++) {
				SFEvent[i](sfEvent);
			}
		}

		for (size_t i = 0; i < UpdateEvent.size(); i++) {
			UpdateEvent[i]();
		}

		window.clear();
		window.draw(player);
		window.display();
	}

	return 0;
}

static std::vector<Keyboard::Key> pressedKeys;
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

void OnKeyDown(Keyboard::Key key) {

}

void OnKey(Keyboard::Key key) {
	if (key == Keyboard::Key::A) {
		player.move(-PLAYER_SPEED, 0);
	} else if (key == Keyboard::Key::D) {
		player.move(PLAYER_SPEED, 0);
	}

	if (key == Keyboard::Key::W) {
		player.move(0, -PLAYER_SPEED);
	} else if (key == Keyboard::Key::S) {
		player.move(0, PLAYER_SPEED);
	}
}

void OnKeyUp(Keyboard::Key key) {

}
