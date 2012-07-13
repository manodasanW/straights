#ifndef GAME_WINDOW
#define GAME_WINDOW

#include <gtkmm/window.h>
#include <gtkmm/box.h>

#include "GameController.h"
#include "PlayFrame.h"
#include "ControlFrame.h"

// Main window
class GameWindow : public Gtk::Window {

public:
	GameWindow(GameController *, Game *);			// constructor - requires controller and facade access to pass onto its children

private:
	Gtk::HBox gameWindow_;							// game consists of one horizontal window which contains everything else
	ControlFrame controlFrame_;						// area where controls are located
	PlayFrame playFrame_;							// area where cards are located

};

#endif /* GAME_WINDOW */
