#include "GameWindow.h"

GameWindow::GameWindow()
	:gameWindow(false, 10) { 
	set_title("Straights");

	gameWindow.add(playFrame);
	gameWindow.add(controlFrame);

	add(gameWindow);
	show_all();
}



GameWindow::~GameWindow(){}
