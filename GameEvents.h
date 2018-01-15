#pragma once

#include <SFML/Graphics.hpp>
#include <functional> 
#include <vector> 

using namespace std;
using namespace sf;

extern vector<function<void(Event)>> SFEvent;
extern vector<function<void()>> DrawEvent;

//Update event with id so it can be removed later	
extern map<string, function<void()>> UpdateEvent;