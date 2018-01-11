#pragma once

#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <functional> 
#include <vector> 
#include "GameEvents.h"

using sf::Event;

vector<function<void(Event)>> SFEvent;
map<std::string, function<void()>> UpdateEvent;
vector<function<void()>> DrawEvent;