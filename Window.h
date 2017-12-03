#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

extern RenderWindow window;
extern map<int, vector<const Drawable*>> drawablesByLayer;
extern vector<const Drawable*> drawablesinorder;

void add_drawable(const Drawable &drawable, int renderLayer);
void draw_drawables_in_order();
