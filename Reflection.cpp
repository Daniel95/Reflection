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
	Clock clock;
	SFEvent.push_back(HandleInputEvents);
	UpdateEvent.push_back(HandleInputUpdate);

	Vector2i windowCenter = windowSize / 2;
	int quarterWindowHeight = windowSize.y / 4;
	Vector2i player1Pos = Vector2i(windowCenter.x, windowCenter.y + quarterWindowHeight);
	Vector2i player2Pos = Vector2i(windowCenter.x, windowCenter.y - quarterWindowHeight);

	Player player1(Vector2f((float)player1Pos.x, (float)player1Pos.y));
	Player player2(Vector2f((float)player2Pos.x, (float)player2Pos.y));

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