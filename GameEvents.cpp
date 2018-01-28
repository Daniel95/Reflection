#pragma once

#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <functional> 
#include <vector> 
#include "GameEvents.h"

using sf::Event;

//Generic events which can be used for all kinds of logic
vector<function<void(Event)>> SFEvent;
map<std::string, function<void()>> UpdateEvent;
vector<function<void()>> DrawEvent;