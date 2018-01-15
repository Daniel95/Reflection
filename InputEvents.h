#pragma once

#include <SFML/Graphics.hpp>
#include <functional> 
#include <vector> 

using namespace std;
using namespace sf;

extern map<string, function<void(Keyboard::Key)>> KeyDownEvent;
extern map<string, function<void(Keyboard::Key)>> KeyEvent;
extern map<string, function<void(Keyboard::Key)>> KeyUpEvent;

extern map<string, function<void(Mouse::Button, Vector2i)>> MouseDownEvent;
extern map<string, function<void(Mouse::Button, Vector2i, Vector2i)>> MouseEvent;
extern map<string, function<void(Mouse::Button, Vector2i)>> MouseUpEvent;

extern Vector2i mouseDelta;

void HandleInputEvents(Event sfEvent);
void HandleInputUpdate();