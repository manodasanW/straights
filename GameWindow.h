#ifndef GAME_WINDOW
#define GAME_WINDOW

#include <gtkmm/window.h>
#include <gtkmm/box.h>

#include "PlayFrame.h"
#include "ControlFrame.h"

class GameWindow : public Gtk::Window {

public:
	GameWindow();
	virtual ~GameWindow();

private:
	Gtk::HBox gameWindow;
	PlayFrame playFrame;
	ControlFrame controlFrame;

};

#endif
