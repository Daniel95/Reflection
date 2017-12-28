#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

static const Vector2i GameWindowSize = Vector2i(1280, 920);
extern RenderWindow GameWindow;
extern map<int, vector<const Drawable*>> DrawablesByLayer;
extern vector<const Drawable*> DrawablesInOrder;

void AddDrawable(const Drawable &drawable, int renderLayer);
void RemoveDrawable(const Drawable &drawable, int renderLayer);
void DrawDrawablesInOrder();
