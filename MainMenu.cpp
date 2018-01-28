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
UIButton* exitButton;
Text howToPlayText;
string mainMenuID = "MainMenuID";

void OnKeyDown(Keyboard::Key key);
void DispatchOnStartClickedEvent();

void StartMainMenu() {
	KeyDownEvent[mainMenuID] = OnKeyDown;

	Vector2f windowCenter = Vector2f((float)GameWindow.getSize().x / 2, (float)GameWindow.getSize().y / 2);

	startButton = new UIButton(windowCenter, Vector2f(200, 100), "Start", Color::Blue);
	startButton->OnClickedEvent[mainMenuID] = DispatchOnStartClickedEvent;
}

void StopMainMenu() {
	KeyDownEvent.erase(mainMenuID);
	startButton->Destroy();
}

void DispatchOnStartClickedEvent() {
	for (size_t i = 0; i < OnStartClickedEvent.size(); i++) {
		OnStartClickedEvent[i]();
	}
}

void OnKeyDown(Keyboard::Key key) {
	if (key != Keyboard::Key::Escape) { return; }
	GameWindow.close();
}