// Reflection.cpp : Defines the entry point for the console application.

#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <functional> 
#include <vector> 
#include <iostream>
#include "InputEvents.h"
#include "GameEvents.h"
#include "Window.h"
#include "Player.h"
#include "TimeHelper.h"

using namespace std;
using namespace sf;

int main() {
	SFEvent.push_back(HandleInputEvents);
	UpdateEvent.push_back(HandleInputUpdate);

	Player player;
	Clock clock;

	while (window.isOpen()) {
		TimeHelper::deltaTime = clock.restart().asSeconds();

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
		draw_drawables_in_order();
		window.display();
	}

	return 0;
}