#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <functional> 
#include "UIButton.h"
#include "Window.h"

using namespace std;
using namespace sf;

extern vector<function<void()>> OnStartClickedEvent;

void StartMainMenu();
void StopMainMenu();