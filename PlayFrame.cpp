#include "PlayFrame.h"

PlayFrame::PlayFrame()
	:playArea(false, 10), table(true, 10), hand(true, 10) { 

	tableFrame.set_label("Cards Played: ");
	handFrame.set_label("Your hand: ");

	for (int tableRowsIndex = 0; tableRowsIndex < NUM_SUITS; tableRowsIndex++)
	{
		tableRows.push_back(new Gtk::HBox(true, 10));
	}
 
	for (int suitIndex = 0; suitIndex < NUM_SUITS; suitIndex++) {
		for (int faceIndex = 0; faceIndex < NUM_FACES; faceIndex++) {
			suitRows[suitIndex][faceIndex] = new Gtk::Image(deckImages.getCardImage(Faces(faceIndex), Suits(suitIndex)));
			tableRows[suitIndex]->add(*suitRows[suitIndex][faceIndex]);	
		}
	}

	for (int handIndex = 0; handIndex < NUM_FACES; handIndex++) {
		handImages[handIndex] = new Gtk::Image(deckImages.getNullCardImage());
		hand.add(*handImages[handIndex]);
	} 	

	for (int tableIndex = 0; tableIndex < NUM_SUITS; tableIndex++) {
		table.add(*tableRows[tableIndex]);
	}

	tableFrame.add(table);
	handFrame.add(hand);

	playArea.add(tableFrame);
	playArea.add(handFrame);

	add(playArea);
}



PlayFrame::~PlayFrame()
{
	for (int suitIndex = 0; suitIndex < NUM_SUITS; suitIndex++) {
		for (int faceIndex = 0; faceIndex < NUM_FACES; faceIndex++) {
			delete suitRows[suitIndex][faceIndex];
		}
	}
	
	for (int handIndex = 0; handIndex < NUM_FACES; handIndex++) {
		delete handImages[handIndex];
	}

	for (unsigned int tableRowsIndex = 0; tableRowsIndex < tableRows.size(); tableRowsIndex++) {
		delete tableRows[tableRowsIndex];
	}
}

