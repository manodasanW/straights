#ifndef PLAY_FRAME
#define PLAY_FRAME

#include "Observer.h"

#include <gtkmm/box.h>
#include <gtkmm/image.h>
#include <gtkmm/label.h>
#include <gtkmm/button.h>
#include <gtkmm/dialog.h>
#include <gtkmm/stock.h>
#include <sigc++/connection.h>

#include <vector>

#include "DeckGUI.h"
#include "GameController.h"

class PlayFrame : public Observer {

public:
	PlayFrame(GameController *, Game *);
	virtual ~PlayFrame();
	void notify();

protected:
    void on_card_play(const Card &);

private:
    GameController *gc_;
    Game *g_;
    
	Gtk::VBox playArea;

	Gtk::Image* suitRows[SUIT_COUNT][RANK_COUNT];
	Gtk::Frame tableFrame;
	Gtk::VBox table;
	std::vector<Gtk::HBox*> tableRows;
    
    Gtk::Button handButtons[RANK_COUNT];
    sigc::connection handButtonConnections[RANK_COUNT];
	Gtk::Image* handImages[RANK_COUNT];
	Gtk::Frame handFrame;
	Gtk::HBox hand;
    
    Gtk::Label dialogLabel;
    Gtk::Dialog invalidMoveDialog;

	DeckGUI deckImages;
};

#endif
