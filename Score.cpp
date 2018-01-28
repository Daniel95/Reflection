#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include "GameEvents.h"
#include "Player.h"
#include "TimeHelper.h"
#include "UIHelper.h"
#include "Window.h"
#include "Score.h"
#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>

using namespace sf;
using namespace std;

const string scoreId = "scoreId";
const Vector2f textSize = Vector2f(1.3f, 1.3f);
const Vector2f textPosition = Vector2f(25, 25);
const int textFontSize = 35;
const Color textFillColor = Color::White;
const Color textOutlineColor = Color::Black;
const int scoreDrawLayer = 0;
const int decimalsToDispay = 0;

Text scoreText;
float score;

void UpdateScore();

float GetScore() {
	return score;
}

string GetScoreString() {
	stringstream stream;
	stream << fixed << setprecision(decimalsToDispay) << score;
	return stream.str();
}

void StartScore() {
	scoreText.setPosition(textPosition);
	scoreText.setFillColor(textFillColor);
	scoreText.setOutlineColor(textOutlineColor);
	scoreText.setScale(textSize);
	scoreText.setCharacterSize(textFontSize);
	scoreText.setFont(GetFont());

	UpdateEvent[scoreId] = UpdateScore;
	AddDrawable(scoreText, scoreDrawLayer);
}

void StopScore() {
	score = 0;

	UpdateEvent.erase(scoreId);
	RemoveDrawable(scoreText, scoreDrawLayer);
}

void UpdateScore() {
	//Add time of the last frame to score
	score += TimeHelper::DeltaTime;

	//reduce to decimals of score to display
	stringstream stream;
	stream << fixed << setprecision(decimalsToDispay) << score;
	scoreText.setString(stream.str());
}
