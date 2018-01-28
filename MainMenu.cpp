#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <functional> 
#include "UIButton.h"
#include "InputEvents.h"
#include "Window.h"

using namespace std;
using namespace sf;

vector<function<void()>> OnStartClickedEvent;

UIButton* startButton;
UIButton* quitButton;
Text howToPlayText;
string mainMenuID = "MainMenuID";

const Vector2f buttonSize = Vector2f(150, 75);

void Quit();
void DispatchOnStartClickedEvent();

void StartMainMenu() {
	Vector2f startButtonPosition = Vector2f((float)GameWindow.getSize().x / 6, (float)GameWindow.getSize().y / 6);

	startButton = new UIButton(startButtonPosition, buttonSize, "Start", Color::Blue);
	startButton->OnClickedEvent[mainMenuID] = DispatchOnStartClickedEvent;

	Vector2f quitButtonPosition = startButtonPosition + Vector2f(0, buttonSize.y * 2);

	quitButton = new UIButton(quitButtonPosition, buttonSize, "Quit", Color::Blue);
	quitButton->OnClickedEvent[mainMenuID] = Quit;
}

void StopMainMenu() {
	KeyDownEvent.erase(mainMenuID);
	startButton->Destroy();
	quitButton->Destroy();
}

void DispatchOnStartClickedEvent() {
	for (size_t i = 0; i < OnStartClickedEvent.size(); i++) {
		OnStartClickedEvent[i]();
	}
}

void Quit() {
	GameWindow.close();
}