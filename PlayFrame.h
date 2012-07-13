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

// Frame which contains the cards and so on
class PlayFrame : public Observer {

public:
	PlayFrame(GameController *, Game *);				// constructor
	virtual ~PlayFrame();								// destructor
	void notify();										// used to notify of updates

protected:
    void on_card_play(const Card &);					// called with card which was played

private:
    GameController *gc_;								// controller - used to call when input on gui occurs such as card click
    Game *g_;											// facade
    
	// GUI elements
	Gtk::VBox playArea;

	Gtk::Image* suitRows[SUIT_COUNT][RANK_COUNT];		// used to store all the images of cards on table
	Gtk::Frame tableFrame;								// frame for table
	Gtk::VBox table;
	std::vector<Gtk::HBox*> tableRows;					// invidual rows on the table storing cards of different suit
    
    Gtk::Button handButtons[RANK_COUNT];				// buttons which are basically the cards in the hand
    sigc::connection handButtonConnections[RANK_COUNT];	// button listeners for the hand buttons
	Gtk::Image* handImages[RANK_COUNT];					// used to store all images of cards on hand
	Gtk::Frame handFrame;								// frame to store hand
	Gtk::HBox hand;
    
	// dialog for invalid moves
    Gtk::Label dialogLabel;
    Gtk::Dialog invalidMoveDialog;

	DeckGUI deckImages;									// used to retrieve images of cards in deck
};

#endif
