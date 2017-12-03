#pragma once

#include <SFML/Graphics.hpp>
#include <functional> 
#include <vector> 

using namespace std;
using namespace sf;

extern vector<function<void(Keyboard::Key)>> KeyDownEvent;
extern vector<function<void(Keyboard::Key)>> KeyEvent;
extern vector<function<void(Keyboard::Key)>> KeyUpEvent;

void HandleInputEvents(Event sfEvent);
void HandleInputUpdate();