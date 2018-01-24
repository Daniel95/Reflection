#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <functional> 
#include <iostream>
#include <vector> 

using namespace std;

//Add a method to this vector so it gets called after 1 frame
vector<function<void()>> delayedMethods;
vector<int> framesToDelay;

void DelayMethod(int _framesToDelay, function<void()> _delayedMethod) {
	delayedMethods.push_back(_delayedMethod);
	framesToDelay.push_back(_framesToDelay);
}

void HandleDelayedMethods() {
	for (int i = delayedMethods.size() - 1; i >= 0; i--) {
		framesToDelay[i]--;
		if (framesToDelay[i] > 0) { continue; }
		delayedMethods[i]();
		delayedMethods.erase(delayedMethods.begin() + i);
		framesToDelay.erase(framesToDelay.begin() + i);
	}
}