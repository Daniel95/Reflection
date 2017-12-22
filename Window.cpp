#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include "Window.h"
#include <iostream>

using namespace sf;
using namespace std;

RenderWindow window(VideoMode(windowSize.x, windowSize.y), "Reflection", Style::Close | Style::Titlebar);
map<int, vector<const Drawable*>> drawablesByLayer;
vector<const Drawable*> drawablesInOrder;

void SortDrawablesInOrder();

void AddDrawable(const Drawable &drawable, int renderLayer) {
	if (drawablesByLayer.find(renderLayer) == drawablesByLayer.end()) {
		drawablesByLayer[renderLayer] = vector<const Drawable*>();
	}
	drawablesByLayer[renderLayer].push_back(&drawable);

	SortDrawablesInOrder();
}


void RemoveDrawable(const Drawable &drawable, int renderLayer) {
	if (drawablesByLayer.find(renderLayer) == drawablesByLayer.end()) {
		cout << "Drawable to remove not found!" << endl;
		return;
	}

	vector<const Drawable*>& drawableVector = drawablesByLayer[renderLayer];
	drawableVector.erase(remove(drawableVector.begin(), drawableVector.end(), &drawable), drawableVector.end());

	if (drawableVector.size() == 0) {
		drawablesByLayer.erase(renderLayer);
	}
}

void DrawDrawablesInOrder() {
	for (size_t i = 0; i < drawablesInOrder.size(); i++) {
		window.draw(*drawablesInOrder[i]);
	}
}

void SortDrawablesInOrder() {
	vector<int> drawableLayers;
	for (auto const& x : drawablesByLayer) {
		drawableLayers.push_back(x.first);
	}

	drawablesInOrder.clear();
	for (int i = drawableLayers.size() - 1; i >= 0; i--) {
		int layer = drawableLayers[i];
		vector<const Drawable*> drawables = drawablesByLayer[layer];
		for (size_t d = 0; d < drawables.size(); d++) {
			drawablesInOrder.push_back(drawables[d]);
		}
	}
}
