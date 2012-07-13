#include "GameWindow.h"

GameWindow::GameWindow(GameController *gc, Game *g) : gameWindow_(false, 10),
    playFrame_(gc, g), controlFrame_(gc, g)
{
	set_title("Straights");
    
	gameWindow_.add(playFrame_);
	gameWindow_.add(controlFrame_);

	add(gameWindow_);
	show_all();
}
