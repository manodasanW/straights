#include "PlayFrame.h"

PlayFrame::PlayFrame(GameController *gc, Game *g)
	: Observer(), gc_(gc), g_(g), playArea(false, 10), table(true, 10), hand(true, 10),
    dialogLabel("That is not a valid move.")
{

	tableFrame.set_label("Cards Played: ");
	handFrame.set_label("Your hand: ");

	for (int tableRowsIndex = 0; tableRowsIndex < SUIT_COUNT; tableRowsIndex++)
	{
		tableRows.push_back(Gtk::manage(new Gtk::HBox(true, 10)));
	}
 
	for (int suitIndex = 0; suitIndex < SUIT_COUNT; suitIndex++) {
		for (int faceIndex = 0; faceIndex < RANK_COUNT; faceIndex++) {
			suitRows[suitIndex][faceIndex] = Gtk::manage(new Gtk::Image(deckImages.getNullCardImage()));
            tableRows[suitIndex]->add(*suitRows[suitIndex][faceIndex]);	
		}
	}

	for (int handIndex = 0; handIndex < RANK_COUNT; handIndex++) {
		handImages[handIndex] = Gtk::manage(new Gtk::Image(deckImages.getNullCardImage()));
        handButtons[handIndex].set_image(*handImages[handIndex]);
        handButtons[handIndex].set_sensitive(false);
        handButtonConnections[handIndex] = sigc::connection();
		hand.add(handButtons[handIndex]);
	}
    
	for (int tableIndex = 0; tableIndex < SUIT_COUNT; tableIndex++) {
		table.add(*tableRows[tableIndex]);
	}

	tableFrame.add(table);
	handFrame.add(hand);

	playArea.add(tableFrame);
	playArea.add(handFrame);

	add(playArea);
    
    // dialog box
    Gtk::VBox *contentArea = invalidMoveDialog.get_vbox();
    contentArea->add(dialogLabel);
    invalidMoveDialog.add_button(Gtk::Stock::OK, Gtk::RESPONSE_OK);
    g_->subscribeView(this);
}

void PlayFrame::notify()
{
    // current player hand
    const CardList c = g_->getCurrentPlayerHand();
    for (int i = 0; i < c.size(); i++) {
        handImages[i] = Gtk::manage(new Gtk::Image(deckImages.getCardImage(c[i]->getRank(), c[i]->getSuit())));
        handButtons[i].set_sensitive(true);
        handButtons[i].set_image(*handImages[i]);
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
        handButtonConnections[i].disconnect();
        handButtonConnections[i] = handButtons[i].signal_clicked().connect( sigc::bind (
            sigc::mem_fun(*this, &PlayFrame::on_card_play), *c[i]));
    }
    for (int i = c.size(); i < 13; i++) {
        handImages[i] = Gtk::manage(new Gtk::Image(deckImages.getNullCardImage()));
        handButtons[i].set_image(*handImages[i]);
        handButtons[i].set_sensitive(false);
        handButtonConnections[i].disconnect();
        handButtonConnections[i] = sigc::connection();
    }
    
    // table
    for (int suitIndex = 0; suitIndex < SUIT_COUNT; suitIndex++) {
        for (int faceIndex = 0; faceIndex < RANK_COUNT; faceIndex++) {
            tableRows[suitIndex]->remove(*suitRows[suitIndex][faceIndex]);
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
}

PlayFrame::~PlayFrame()
{
}

void PlayFrame::on_card_play(const Card &c) {
    gc_->setHintRequestedFlag(false);
    bool validMoveMade = gc_->playCard(c);
    if (!validMoveMade) {
        invalidMoveDialog.show_all_children();
        int result = invalidMoveDialog.run();
        if (result == Gtk::RESPONSE_OK) {
            invalidMoveDialog.hide();
        }
    }
}
