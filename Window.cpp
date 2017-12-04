#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include "Window.h"
#include <iostream>

using namespace sf;
using namespace std;

RenderWindow window(VideoMode(1280, 920), "Reflection", Style::Close | Style::Titlebar);
map<int, vector<const Drawable*>> drawablesByLayer;
vector<const Drawable*> drawablesinorder;

void sort_drawables_in_order();

void add_drawable(const Drawable &drawable, int renderLayer) {
	if (drawablesByLayer.find(renderLayer) == drawablesByLayer.end()) {
		drawablesByLayer[renderLayer] = vector<const Drawable*>();
	}
	drawablesByLayer[renderLayer].push_back(&drawable);

	sort_drawables_in_order();
}

void draw_drawables_in_order() {
	for (size_t i = 0; i < drawablesinorder.size(); i++) {
		window.draw(*drawablesinorder[i]);
	}
}

void sort_drawables_in_order() {
	vector<int> drawableLayers;
	for (auto const& x : drawablesByLayer) {
		drawableLayers.push_back(x.first);
	}

	drawablesinorder.clear();
	for (int i = drawableLayers.size() - 1; i >= 0; i--) {
		int layer = drawableLayers[i];
		vector<const Drawable*> drawables = drawablesByLayer[layer];
		for (size_t d = 0; d < drawables.size(); d++) {
			drawablesinorder.push_back(drawables[d]);
		}
	}
}
