#pragma once

#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

Font font;
bool loaded;

Font& GetFont() {
	if (!loaded) { 
		if (!font.loadFromFile("Resources/Fonts/VCR.ttf")) {
			cout << "Failed to load font" << endl;
		} else {
			loaded = true;
		}
	}

	return font;
}