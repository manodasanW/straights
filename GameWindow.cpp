#include "GameWindow.h"

GameWindow::GameWindow(GameController &gc) : gc_(gc), gameWindow_(false, 10),
    playFrame_(PlayFrame(gc)), controlFrame_(ControlFrame(gc))
{
	set_title("Straights");
    
	gameWindow_.add(playFrame_);
	gameWindow_.add(controlFrame_);

	add(gameWindow_);
	show_all();
}
