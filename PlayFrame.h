#ifndef PLAY_FRAME
#define PLAY_FRAME

#include "Observer.h"

#include <gtkmm/box.h>
#include <gtkmm/image.h>

#include <vector>

#include "DeckGUI.h"
#include "GameController.h"

class PlayFrame : public Observer {

public:
	PlayFrame(GameController *, Game *);
	virtual ~PlayFrame();
	void notify();

private:
    GameController *gc_;
    Game *g_;
    
	Gtk::VBox playArea;

	Gtk::Image* suitRows [SUIT_COUNT][RANK_COUNT];
	Gtk::Frame tableFrame;
	Gtk::VBox table;
	std::vector<Gtk::HBox*> tableRows;

	Gtk::Image* handImages [RANK_COUNT];
	Gtk::Frame handFrame;
	Gtk::HBox hand;

	DeckGUI deckImages;
};

#endif
