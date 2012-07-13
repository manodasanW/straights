#ifndef GAME_WINDOW
#define GAME_WINDOW

#include <gtkmm/window.h>
#include <gtkmm/box.h>

#include "GameController.h"
#include "PlayFrame.h"
#include "ControlFrame.h"

class GameWindow : public Gtk::Window {

public:
	GameWindow(GameController *, Game *);

private:
	Gtk::HBox gameWindow_;
	PlayFrame playFrame_;
	ControlFrame controlFrame_;

};

#endif
