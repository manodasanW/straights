#include "PlayFrame.h"

PlayFrame::PlayFrame(GameController *gc, Game *g)
	: Observer(), gc_(gc), g_(g), playArea(false, 10), table(true, 10), hand(true, 10)
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
		hand.add(*handImages[handIndex]);
	} 	

	for (int tableIndex = 0; tableIndex < SUIT_COUNT; tableIndex++) {
		table.add(*tableRows[tableIndex]);
	}

	tableFrame.add(table);
	handFrame.add(hand);

	playArea.add(tableFrame);
	playArea.add(handFrame);

	add(playArea);
        
    g_->subscribeView(this);
}

void PlayFrame::notify()
{
    // current player hand
    int currPlayerIndex = g_->getCurrentPlayerId();
    const CardList c = g_->getPlayerHand(currPlayerIndex);
    for (int i = 0; i < c.size(); i++) {
        hand.remove(*handImages[i]);
        handImages[i] = Gtk::manage(new Gtk::Image(deckImages.getCardImage(c[i]->getRank(), c[i]->getSuit())));
        hand.add(*handImages[i]);
    }
    for (int i = c.size(); i < 13; i++) {
        hand.remove(*handImages[i]);
        handImages[i] = Gtk::manage(new Gtk::Image(deckImages.getNullCardImage()));
        hand.add(*handImages[i]);
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

