#include "PlayFrame.h"

using namespace std;

// constructor - sets up all the gui elements on the frame
PlayFrame::PlayFrame(GameController *gc, Game *g)
	: Observer(), gc_(gc), g_(g), playArea(false, 10), table(true, 10), hand(true, 10),
    dialogLabel("That is not a valid move.")
{

	// sets up the labels
	tableFrame.set_label("Cards Played: ");
	handFrame.set_label("Your hand: ");

	// sets up the horizontal boxes to store cards of diff suit in table
	for (int tableRowsIndex = 0; tableRowsIndex < SUIT_COUNT; tableRowsIndex++)
	{
		tableRows.push_back(Gtk::manage(new Gtk::HBox(true, 10)));
	}

	// sets up the table with null cards 
	for (int suitIndex = 0; suitIndex < SUIT_COUNT; suitIndex++) {
		for (int faceIndex = 0; faceIndex < RANK_COUNT; faceIndex++) {
			suitRows[suitIndex][faceIndex] = Gtk::manage(new Gtk::Image(deckImages.getNullCardImage()));
            tableRows[suitIndex]->add(*suitRows[suitIndex][faceIndex]);	
		}
	}

	// sets the images in hand to null card, and un clickable
	for (int handIndex = 0; handIndex < RANK_COUNT; handIndex++) {
		handImages[handIndex] = Gtk::manage(new Gtk::Image(deckImages.getNullCardImage()));
        handButtons[handIndex].set_image(*handImages[handIndex]);
        handButtons[handIndex].set_sensitive(false);
        handButtonConnections[handIndex] = sigc::connection();
		hand.add(handButtons[handIndex]);
	}
    
	// adds all the rows in the table
	for (int tableIndex = 0; tableIndex < SUIT_COUNT; tableIndex++) {
		table.add(*tableRows[tableIndex]);
	}

	// adds gui element set up to frame
	tableFrame.add(table);
	handFrame.add(hand);

	playArea.add(tableFrame);
	playArea.add(handFrame);

	add(playArea);
    
    // sets up dialog boxes
    Gtk::VBox *contentArea = invalidMoveDialog.get_vbox();
    contentArea->add(dialogLabel);
	// adds ok button
    invalidMoveDialog.add_button(Gtk::Stock::OK, Gtk::RESPONSE_OK);
    winnersDialog.add_button(Gtk::Stock::OK, Gtk::RESPONSE_OK);
    
	// requests facade to tell player that it needs to be notified of updates
    g_->subscribeView(this);
}

// performs gui update due to model changed
void PlayFrame::notify()
{
    // current player hand
    const CardList c = g_->getCurrentPlayerHand();
	// sets up the cards in the hand
    for (int i = 0; i < c.size(); i++) {
        handImages[i] = Gtk::manage(new Gtk::Image(deckImages.getCardImage(c[i]->getRank(), c[i]->getSuit())));
		// makes cards clickable
        handButtons[i].set_sensitive(true);
        handButtons[i].set_image(*handImages[i]);
		// displays border if the current card is a hint
        if (gc_->hintRequested()) {
            if (*g_->hint() == *c[i]) {
                handButtons[i].drag_highlight();
            }
            else {
                handButtons[i].drag_unhighlight();
            }
        }
        else {
            handButtons[i].drag_unhighlight();
        }
		// unregisters all previous click listeners on button and sets up new one
        handButtonConnections[i].disconnect();
        handButtonConnections[i] = handButtons[i].signal_clicked().connect( sigc::bind (
            sigc::mem_fun(*this, &PlayFrame::on_card_play), *c[i]));
    }
	// sets up the empty spots in the hand
    for (int i = c.size(); i < 13; i++) {
        handImages[i] = Gtk::manage(new Gtk::Image(deckImages.getNullCardImage()));
        handButtons[i].set_image(*handImages[i]);
		// makes them unclickable
        handButtons[i].set_sensitive(false);
		// disconnects all listeners
        handButtonConnections[i].disconnect();
        handButtonConnections[i] = sigc::connection();
    }
    
    // sets up the cards in the table
    for (int suitIndex = 0; suitIndex < SUIT_COUNT; suitIndex++) {
        for (int faceIndex = 0; faceIndex < RANK_COUNT; faceIndex++) {
			// removes any previous cards
            tableRows[suitIndex]->remove(*suitRows[suitIndex][faceIndex]);

			// adds card to table gui if in table
            if (g_->getTable().find(Card((Suit)suitIndex, (Rank)faceIndex)) != -1) {
                suitRows[suitIndex][faceIndex] = Gtk::manage(new Gtk::Image(deckImages.getCardImage((Rank)faceIndex, (Suit)suitIndex)));
            }
            else {
                suitRows[suitIndex][faceIndex] = Gtk::manage(new Gtk::Image(deckImages.getNullCardImage()));
            }
            tableRows[suitIndex]->add(*suitRows[suitIndex][faceIndex]);	
        }
    }
    
    show_all();
    
    // if game over, print winners
    if (g_->gameDone()) {
        string msg;
        for (int i = 0; i < 4; i++) {
            if (g_->winner(i)) {
                msg += "Player " + helper::num2str(i+1) + " wins!\n";
            }
        }
        winnersLabel.set_label(msg.c_str());
        Gtk::VBox *contentArea = winnersDialog.get_vbox();
        contentArea->add(winnersLabel);
        winnersDialog.show_all_children();
        int result = winnersDialog.run();
        if (result == Gtk::RESPONSE_OK) {
            winnersDialog.hide();
        }
    }
}

// destructor
PlayFrame::~PlayFrame()
{
}

// called when card is clicked on to play
void PlayFrame::on_card_play(const Card &c) {
    gc_->setHintRequestedFlag(false);
    bool validMoveMade = gc_->playCard(c);

	// if it is not a valid move, displays dialog box
    if (!validMoveMade) {
        invalidMoveDialog.show_all_children();

		// waits till user clicks ok on dialog
        int result = invalidMoveDialog.run();
        if (result == Gtk::RESPONSE_OK) {
            invalidMoveDialog.hide();
        }
    }
}
