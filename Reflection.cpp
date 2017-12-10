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
#include "Box.h"

using namespace std;
using namespace sf;

int main() {
	Clock clock;
	SFEvent.push_back(HandleInputEvents);
	UpdateEvent.push_back(HandleInputUpdate);

	Vector2i windowCenter = windowSize / 2;
	int quarterWindowHeight = windowSize.y / 4;
	Vector2f player1Pos = Vector2f((float)windowCenter.x, (float)windowCenter.y + (float)quarterWindowHeight);
	Vector2f player2Pos = Vector2f((float)windowCenter.x, (float)windowCenter.y - (float)quarterWindowHeight);

	Player player1(Vector2f(player1Pos.x, player1Pos.y));
	Player player2(Vector2f(player2Pos.x, player2Pos.y));

	Box box1(Vector2f(player1Pos.x + 200, player1Pos.y), Vector2f(50, 100));
	Box box2(Vector2f(player2Pos.x - 300, player2Pos.y), Vector2f(300, 100));
	Box box3(Vector2f(player2Pos.x, player2Pos.y + 400), Vector2f(200, 23));

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

		box1.GetCollider().CheckCollision(player1.GetCollider(), 0.0f);
		box1.GetCollider().CheckCollision(player2.GetCollider(), 0.0f);

		box2.GetCollider().CheckCollision(player1.GetCollider(), 0.5f);
		box2.GetCollider().CheckCollision(player2.GetCollider(), 0.5f);

		box3.GetCollider().CheckCollision(player1.GetCollider(), 1.0f);
		box3.GetCollider().CheckCollision(player2.GetCollider(), 1.0f);

		window.clear();
		draw_drawables_in_order();
		window.display();
	}

	return 0;
}