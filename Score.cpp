#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include "GameEvents.h"
#include "Player.h"
#include "TimeHelper.h"
#include "Window.h"
#include <iostream>
#include <string>

using namespace sf;
using namespace std;

const string scoreId = "scoreId";
const Vector2f textSize = Vector2f(1, 1);
const Vector2f textPosition = Vector2f(10, 10);
const int textFontSize = 30;
const Color textFillColor = Color::White;
const Color textOutlineColor = Color::Black;
const int scoreDrawLayer = 0;

Text scoreText;
Font font;

float score;

void StartScore(Player* player);
void StopScore();
void UpdateScore();

void InitScore() {

	if (!font.loadFromFile("Resources/Fonts/VCR.ttf")) {
		cout << "Failed to load font" << endl;
	}

	scoreText.setPosition(textPosition);
	scoreText.setFillColor(textFillColor);
	scoreText.setOutlineColor(textOutlineColor);
	scoreText.setScale(textSize);
	scoreText.setCharacterSize(textFontSize);
	scoreText.setFont(font);
	scoreText.setString("hallo");

	PlayerSpawnedEvent[scoreId] = StartScore;
	PlayerKilledEvent[scoreId] = StopScore;
}

void StartScore(Player* player) {
	UpdateEvent[scoreId] = UpdateScore;
	AddDrawable(scoreText, scoreDrawLayer);
}

void StopScore() {
	UpdateEvent.erase(scoreId);
	RemoveDrawable(scoreText, scoreDrawLayer);
}

void UpdateScore() {
	score += TimeHelper::DeltaTime;
	scoreText.setString(to_string(score));
}
