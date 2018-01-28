#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <functional> 
#include <string> 
#include "UIButton.h"
#include "UIHelper.h"
#include "InputEvents.h"
#include "Score.h"
#include "Window.h"

using namespace std;
using namespace sf;

vector<function<void()>> OnStartClickedEvent;

const Vector2f buttonSize = Vector2f(170, 90);
const string titleString = "Hardlink";
const string howToPlayString = " In this game you control two players at the same time. \n These players are a reflection of each other and are physically linked. \n Survive as long as possible in this sidescroller by moving with WASD \n and shooting by aiming and holding down the left mouse button. \n Your score can be seen in the top left corner and will be accumulated over time. \n When you get hit by an enemy, it's game over. \n You can press Escape at all times to quit the game.";
const string lastScoreString = "Your last score was ";
const int mainMenuCharacterText = 26;
const int mainMenuCharacterTitleText = 50;

UIButton* startButton;
UIButton* quitButton;
Text titleText;
Text howToPlayText;
Text lastScoreText;
string mainMenuID = "MainMenuID";

void Quit();
void DispatchOnStartClickedEvent();

void StartMainMenu() {
	//Start button
	Vector2f startButtonPosition = Vector2f((float)GameWindow.getSize().x / 8, (float)GameWindow.getSize().y / 4);

	startButton = new UIButton(startButtonPosition, buttonSize, "Start", Color::Blue);
	startButton->OnClickedEvent[mainMenuID] = DispatchOnStartClickedEvent;

	//Quit button
	Vector2f quitButtonPosition = startButtonPosition + Vector2f(0, buttonSize.y * 2);

	quitButton = new UIButton(quitButtonPosition, buttonSize, "Quit", Color::Blue);
	quitButton->OnClickedEvent[mainMenuID] = Quit;

	//Title text
	titleText.setString(titleString);
	titleText.setCharacterSize(mainMenuCharacterTitleText);
	titleText.setFont(GetFont());
	titleText.setOrigin(titleText.getLocalBounds().left + titleText.getLocalBounds().width / 2.0f, titleText.getLocalBounds().top + titleText.getLocalBounds().height / 2.0f);

	Vector2f titleTextPosition = Vector2f((float)GameWindow.getSize().x / 2, 100);
	titleText.setPosition(titleTextPosition);

	AddDrawable(titleText, 0);

	//How to play text
	howToPlayText.setString(howToPlayString);
	howToPlayText.setCharacterSize(mainMenuCharacterText);
	howToPlayText.setFont(GetFont());
	howToPlayText.setOrigin(howToPlayText.getLocalBounds().left + howToPlayText.getLocalBounds().width / 2.0f, howToPlayText.getLocalBounds().top + howToPlayText.getLocalBounds().height / 2.0f);

	Vector2f howToPlayTextPosition = quitButtonPosition + Vector2f(howToPlayText.getGlobalBounds().width / 2 - quitButton->GetBody().getSize().x / 2, howToPlayText.getGlobalBounds().height / 2.0f + 250);
	howToPlayText.setPosition(howToPlayTextPosition);

	AddDrawable(howToPlayText, 0);

	//Display your last score if it exists
	if (GetScore() == 0) { return; }
	lastScoreText.setString(lastScoreString + GetScoreString() + ".");
	lastScoreText.setCharacterSize(mainMenuCharacterText);
	lastScoreText.setFont(GetFont());
	lastScoreText.setOrigin(lastScoreText.getLocalBounds().left + lastScoreText.getLocalBounds().width / 2.0f, lastScoreText.getLocalBounds().top + lastScoreText.getLocalBounds().height / 2.0f);

	Vector2f lastScoreTextPosition = startButtonPosition + Vector2f(lastScoreText.getGlobalBounds().width / 2 + startButton->GetBody().getSize().x / 2 + 100, 0);
	lastScoreText.setPosition(lastScoreTextPosition);

	AddDrawable(lastScoreText, 0);
}

void StopMainMenu() {
	startButton->Destroy();
	quitButton->Destroy();

	RemoveDrawable(howToPlayText, 0);
	RemoveDrawable(titleText, 0);

	if (GetScore() == 0) { return; }
	RemoveDrawable(lastScoreText, 0);
}

void DispatchOnStartClickedEvent() {
	for (size_t i = 0; i < OnStartClickedEvent.size(); i++) {
		OnStartClickedEvent[i]();
	}
}

void Quit() {
	GameWindow.close();
}