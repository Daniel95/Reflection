#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include "Window.h"
#include <iostream>

using namespace sf;
using namespace std;

//RenderWindow GameWindow(VideoMode::getFullscreenModes()[0], "Reflection", Style::Close | Style::Fullscreen);
RenderWindow GameWindow(VideoMode(1280, 920), "Reflection", Style::Close);
map<int, vector<const Drawable*>> DrawablesByLayer;
vector<const Drawable*> DrawablesInOrder;

void SortDrawablesInOrder();

void AddDrawable(const Drawable &drawable, int renderLayer) {
	if (DrawablesByLayer.find(renderLayer) == DrawablesByLayer.end()) {
		DrawablesByLayer[renderLayer] = vector<const Drawable*>();
	}
	DrawablesByLayer[renderLayer].push_back(&drawable);

	SortDrawablesInOrder();
}

void RemoveDrawable(const Drawable &drawable, int renderLayer) {
	if (DrawablesByLayer.find(renderLayer) == DrawablesByLayer.end()) {
		cout << "Drawable to remove not found!" << endl;
		return;
	}

	vector<const Drawable*> &drawableVector = DrawablesByLayer[renderLayer];
	drawableVector.erase(remove(drawableVector.begin(), drawableVector.end(), &drawable), drawableVector.end());

	if (drawableVector.size() == 0) {
		DrawablesByLayer.erase(renderLayer);
	}

	DrawablesInOrder.erase(remove(DrawablesInOrder.begin(), DrawablesInOrder.end(), &drawable), DrawablesInOrder.end());
}

void DrawDrawablesInOrder() {
	for (size_t i = 0; i < DrawablesInOrder.size(); i++) {
		GameWindow.draw(*DrawablesInOrder[i]);
	}
}

void SortDrawablesInOrder() {
	vector<int> drawableLayers;
	for (auto const& x : DrawablesByLayer) {
		drawableLayers.push_back(x.first);
	}

	DrawablesInOrder.clear();
	for (int i = drawableLayers.size() - 1; i >= 0; i--) {
		int layer = drawableLayers[i];
		vector<const Drawable*> drawables = DrawablesByLayer[layer];
		for (size_t d = 0; d < drawables.size(); d++) {
			DrawablesInOrder.push_back(drawables[d]);
		}
	}
}
