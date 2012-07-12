#ifndef PLAY_FRAME
#define PLAY_FRAME

#include <gtkmm/box.h>
#include <gtkmm/image.h>

#include <vector>

#include "DeckGUI.h"
#include "Observer.h"

class PlayFrame : public Observer {

public:
	PlayFrame();
	virtual ~PlayFrame();
	void notify();

private:
	Gtk::VBox playArea;

	Gtk::Image* suitRows [NUM_SUITS][NUM_FACES];
	Gtk::Frame tableFrame;
	Gtk::VBox table;
	std::vector<Gtk::HBox*> tableRows;

	Gtk::Image* handImages [NUM_FACES];
	Gtk::Frame handFrame;
	Gtk::HBox hand;

	DeckGUI deckImages;
};

#endif
