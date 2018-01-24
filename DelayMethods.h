#pragma once
#include <SFML/Graphics.hpp>
#include <functional> 
#include <vector> 

using namespace std;

void DelayMethod(int framesToDelay, function<void()> delayedMethod);
void HandleDelayedMethods();