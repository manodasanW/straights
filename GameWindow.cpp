#include "GameWindow.h"

// constructor - initalizes all gui elements
GameWindow::GameWindow(GameController *gc, Game *g) : gameWindow_(false, 10),
    playFrame_(gc, g), controlFrame_(gc, g)
{
	// sets title
	set_title("Straights");
    
	// adds the play area and control area
	gameWindow_.add(playFrame_);
	gameWindow_.add(controlFrame_);

	add(gameWindow_);
	// displays all elements
	show_all();
}
