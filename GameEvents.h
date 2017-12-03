#pragma once

#include <SFML/Graphics.hpp>
#include <functional> 
#include <vector> 

using namespace std;
using namespace sf;

extern vector<function<void(Event)>> SFEvent;
extern vector<function<void()>> UpdateEvent;
extern vector<function<void()>> DrawEvent;