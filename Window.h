#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

static const Vector2i windowSize = Vector2i(1280, 920);
extern RenderWindow window;
extern map<int, vector<const Drawable*>> drawablesByLayer;
extern vector<const Drawable*> drawablesInOrder;

void AddDrawable(const Drawable &drawable, int renderLayer);
void RemoveDrawable(const Drawable &drawable, int renderLayer);
void DrawDrawablesInOrder();
