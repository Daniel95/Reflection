#pragma once

#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <functional> 
#include <vector> 
#include "GameEvents.h"

using namespace std;
using namespace sf;

vector<function<void(Event)>> SFEvent;
map<string, function<void()>> UpdateEvent;
vector<function<void()>> DrawEvent;