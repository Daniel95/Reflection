// Reflection.cpp : Defines the entry point for the console application.

#include "stdafx.h"
#include <SFML/Graphics.hpp>

#include <functional> //-
#include <vector> //-

using namespace std;
using namespace sf;

static std::vector<std::function<void(Keyboard::Key)>> KeyDownEvent;

static CircleShape player(100.f);
const float PLAYER_SPEED = 1;


void OnKeyDown(Keyboard::Key key) {
	printf("Text Entered ", key);

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


int main() {

	RenderWindow window(VideoMode(1280, 920), "Reflection", Style::Close | Style::Titlebar);
	player.setFillColor(Color::Green);

	KeyDownEvent.push_back(OnKeyDown);

	while (window.isOpen()) {
		Event sfEvent;
		while (window.pollEvent(sfEvent)) {
			switch (sfEvent.type) {
				case Event::Closed:
					window.close();
					break;
				case Event::TextEntered:
					if (sfEvent.text.unicode < 128) {
						for (size_t i = 0; i < KeyDownEvent.size(); i++) {
							KeyDownEvent[i](static_cast<Keyboard::Key>(sfEvent.text.unicode));
						}
						printf("%c", sfEvent.text.unicode);
					}
			}

			if (sfEvent.type == Event::Closed) {
				window.close();
			}

		}

		window.clear();
		window.draw(player);
		window.display();
	}

	return 0;
}