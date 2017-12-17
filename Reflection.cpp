// Reflection.cpp : Defines the entry point for the console application.

#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <functional> 
#include <vector> 
#include <iostream>
#include "InputEvents.h"
#include "GameEvents.h"
#include "Window.h"
#include "Collisions.h"
#include "Player.h"
#include "TimeHelper.h"
#include "Box.h"

using namespace std;
using namespace sf;

int main() {
	Clock clock;
	SFEvent.push_back(HandleInputEvents);
	UpdateEvent.push_back(HandleInputUpdate);

	Vector2f windowCenter = Vector2f((float)windowSize.x / 2, (float)windowSize.y / 2);
	float quarterWindowHeight = (float)windowSize.y / 4;
	Vector2f player1Pos = Vector2f(windowCenter.x, windowCenter.y + quarterWindowHeight);
	Vector2f player2Pos = Vector2f(windowCenter.x, windowCenter.y - quarterWindowHeight);

	Player player1(Vector2f(player1Pos.x, player1Pos.y));
	Player player2(Vector2f(player2Pos.x, player2Pos.y));

	Box box1(Vector2f(player1Pos.x + 200, player1Pos.y), Vector2f(57, 204), 100.0f);
	Box box2(Vector2f(player1Pos.x + 280, player1Pos.y + 150), Vector2f(50, 100), 0.5f);
	Box box3(Vector2f(player2Pos.x - 355, player2Pos.y), Vector2f(100, 162), 10.0f);
	Box box4(Vector2f(player2Pos.x - 133, player2Pos.y + 200), Vector2f(79, 135), 1.5f);
	Box box5(Vector2f(player2Pos.x - 320, player2Pos.y - 100), Vector2f(60, 112), 100.0f);
	Box box6(Vector2f(player2Pos.x + 450, player2Pos.y + 300), Vector2f(37, 190), 0.1f);

	Box topBoundary(Vector2f(windowCenter.x, 0), Vector2f((float)windowSize.x, 50), 9999);
	Box bottomBoundary(Vector2f(windowCenter.x, (float)windowSize.y), Vector2f((float)windowSize.x, 50), 9999);
	Box rightBoundary(Vector2f(0, windowCenter.y), Vector2f(0, (float)windowSize.y), 9999);
	Box leftBoundary(Vector2f((float)windowSize.x, windowCenter.y), Vector2f(0, (float)windowSize.y), 9999);

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

		UpdateCollisions();

		window.clear();
		draw_drawables_in_order();
		window.display();
	}

	return 0;
}