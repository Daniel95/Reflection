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
const Vector2f textSize = Vector2f(100, 100);
const Vector2f textPosition = Vector2f(100, 100);
const Color textColor = Color::White;

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
	scoreText.setFillColor(textColor);
	scoreText.setScale(textSize);
	scoreText.setCharacterSize(30);	
	scoreText.setFont(font);
	scoreText.setString("hallo");

	PlayerSpawnedEvent[scoreId] = StartScore;
	PlayerKilledEvent[scoreId] = StopScore;
}

void StartScore(Player* player) {
	UpdateEvent[scoreId] = UpdateScore;
	AddDrawable(scoreText, 2);
}

void StopScore() {
	UpdateEvent.erase(scoreId);
	RemoveDrawable(scoreText, 2);
}

void UpdateScore() {
	score += TimeHelper::DeltaTime;
	scoreText.setString(to_string(score));
}
