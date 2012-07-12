#include "GameWindow.h"

GameWindow::GameWindow(GameController &gc) : gc_(gc), gameWindow_(false, 10),
    playFrame_(gc), controlFrame_(gc)
{
	set_title("Straights");
    
	gameWindow_.add(playFrame_);
	gameWindow_.add(controlFrame_);

	add(gameWindow_);
	show_all();
}
