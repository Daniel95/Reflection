#pragma once

#include <SFML/Graphics.hpp>
#include <functional> 
#include <vector> 

using namespace std;
using namespace sf;

extern vector<function<void(Keyboard::Key)>> KeyDownEvent;
extern vector<function<void(Keyboard::Key)>> KeyEvent;
extern vector<function<void(Keyboard::Key)>> KeyUpEvent;

extern vector<function<void(Mouse::Button, Vector2i)>> MouseDownEvent;
extern vector<function<void(Mouse::Button, Vector2i, Vector2i)>> MouseEvent;
extern vector<function<void(Mouse::Button, Vector2i)>> MouseUpEvent;

extern Vector2i mouseDelta;

void HandleInputEvents(Event sfEvent);
void HandleInputUpdate();