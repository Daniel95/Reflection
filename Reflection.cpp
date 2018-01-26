// Reflection.cpp : Defines the entry point for the console application.

#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <functional> 
#include <vector> 
#include <iostream>
#include "Reflection.h"
#include "InputEvents.h"
#include "Score.h"
#include "GameEvents.h"
#include "Window.h"
#include "Collisions.h"
#include "DelayMethods.h"
#include "Level.h"
#include "Player.h"
#include "TimeHelper.h"
#include "Box.h"

using namespace std;
using namespace sf;

map<string, function<void()>> DestroyAllGameObjectsEvent;
string mainId = "MainId";

int main() {
	Clock clock;
	SFEvent.push_back(HandleInputEvents);
	UpdateEvent["HandleInputUpdate"] = HandleInputUpdate;

	InitScore();
	StartLevel();
	KeyDownEvent[mainId] = OnKeyDown;

	while (GameWindow.isOpen()) {
		TimeHelper::DeltaTime = clock.restart().asSeconds();

		HandleDelayedMethods();

		Event sfEvent;
		while (GameWindow.pollEvent(sfEvent)) {
			switch (sfEvent.type) {
				case Event::Closed:
					GameWindow.close();
					break;
			}

			for (size_t i = 0; i < SFEvent.size(); i++) {
				SFEvent[i](sfEvent);
			}
		}

		for (auto const& x : UpdateEvent) {
			x.second();
		}

		UpdateCollisions();

		GameWindow.clear();
		DrawDrawablesInOrder();
		GameWindow.display();
	}

	return 0;
}

void OnKeyDown(Keyboard::Key key) {
	if (key != Keyboard::Key::Escape) { return; }
	GameWindow.close();
}