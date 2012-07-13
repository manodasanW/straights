#include "ControlFrame.h"
#include <string>
#include <iostream>
#include <sstream>

using namespace std;

// helper name space
namespace helper {
	// converts number to string
    string num2str(int n) {
        stringstream ss;
        ss << n;
        return ss.str();
    }
    
	// converts string to number
    int str2num(string s) {
        stringstream ss(s);
        int n;
        return (ss >> n) ? n : 0;
    }
}

// constructor - sets up all the elements on the frame
ControlFrame::ControlFrame(GameController *gc, Game *g)
    : Observer(), gc_(gc), g_(g), controlArea(false, 10), mainControlFrame("Game Controls"), mainControl(true, 10),
    mainButtons(true, 10), startButton("Start Game"), endButton("End Game"), seedEntryControl(false, 10),
    seedEntryLabel("Seed:"), playerControlFrame("Player Controls"), playerControl(false, 10),
    currentPlayer("Current Player: (none)"), playerControlButtons(true, 10), rageButton("Ragequit"),
    hintButton("Hint"), statsControlFrame("Stats"), statsControl(true, 10)
{
    // main control frame components (start/end, seed entry)
    mainButtons.add(startButton);
    mainButtons.add(endButton);
    mainControl.add(mainButtons);
    
    seedEntry.set_max_length(10);
    seedEntry.set_width_chars(10);
    seedEntryControl.add(seedEntryLabel);
    seedEntryControl.add(seedEntry);
    mainControl.add(seedEntryControl);
    
    mainControlFrame.add(mainControl);
    
    // player control frame components
    playerControl.add(currentPlayer);
    playerControl.add(playerControlButtons);
    playerControlButtons.add(rageButton);
    playerControlButtons.add(hintButton);
    playerControlFrame.add(playerControl);
    
    // stats control frame components
    for (int i = 0; i < 4; i++) {
        playerInfoLabels[i].set_label(string("Player " + helper::num2str(i+1)).c_str());
        playerScores[i].set_label("Score: 0\nDiscards: 0");
        playerTypes[i].set_label("Human");
        playerTypeBools[i] = false;
        playerTypes[i].signal_clicked().connect( sigc::bind (
            sigc::mem_fun(*this, &ControlFrame::on_player_type_click), i)
        );
        playerInfoBoxes[i].add(playerInfoLabels[i]);
        playerInfoBoxes[i].add(playerTypes[i]);
        statsControl.add(playerInfoBoxes[i]);
    }
    statsControlFrame.add(statsControl);
    
    // register buttons with clicking events
    startButton.signal_clicked().connect( sigc::mem_fun(*this, &ControlFrame::on_start_click) );
    endButton.signal_clicked().connect( sigc::mem_fun(*this, &ControlFrame::on_end_click) );
    rageButton.signal_clicked().connect( sigc::mem_fun(*this, &ControlFrame::on_ragequit_click) );
    hintButton.signal_clicked().connect( sigc::mem_fun(*this, &ControlFrame::on_hint_click) );
    
    endButton.set_sensitive(false);
    
    // finally, add each major part of the control frame
    controlArea.add(mainControlFrame);
    controlArea.add(playerControlFrame);
    controlArea.add(statsControlFrame);
    add(controlArea);
    
    // subscribe self to observers
    g_->subscribeView(this);
}

// destructor
ControlFrame::~ControlFrame() {
}

// called to update the view
void ControlFrame::notify()
{
    // update display of whose turn it is
    int currPlayer = g_->getCurrentPlayerId() + 1;
    currentPlayer.set_label(string("Current Player: " + helper::num2str(currPlayer)).c_str());
    
    // update score displays
    for (int i = 0; i < 4; i++) {
        playerScores[i].set_label(string("Score: " + helper::num2str(g_->getScore(i))
            + "\nDiscards: " + helper::num2str(g_->getDiscardCount(i))).c_str());
    }
}

// called when start is clicked
void ControlFrame::on_start_click() {
	// displays the scores, and removes the human/ai selection
    if (!gc_->gameInProgress()) {
        for (int i = 0; i < 4; i++) {
            playerInfoBoxes[i].remove(playerTypes[i]);
            playerInfoBoxes[i].add(playerScores[i]);
        }
    }
	
	// enables end button, disables start 
    startButton.set_sensitive(false);
    endButton.set_sensitive(true);
    
	// shows all elements on screen
    show_all();
    
	// sets the seed, and requests to start the game
    string seed_str = seedEntry.get_text();
    gc_->startGame(helper::str2num(seed_str), playerTypeBools);
}

// called when end game is clicked
void ControlFrame::on_end_click() {
	// disables hint
    gc_->setHintRequestedFlag(false);

	// displays human/ai selection
    if (gc_->gameInProgress()) {
        for (int i = 0; i < 4; i++) {
            playerInfoBoxes[i].remove(playerScores[i]);
            playerInfoBoxes[i].add(playerTypes[i]);
        }
    }

	// enables start game button
    startButton.set_sensitive(true);
    endButton.set_sensitive(false);
    
	// removes current player counter, and tells controller to end the game
    currentPlayer.set_label("Current Player: (none)");
    gc_->endGame();
    
    show_all();
}

// Changes given player to the opposite of the current (AI or human), changes to AI when human hits ragequit
void ControlFrame::on_player_type_click(int id) {
    playerTypeBools[id] = !playerTypeBools[id];

	// sets appropriate label on human/ai button depending on what player changed to
    if (playerTypeBools[id]) {
        playerTypes[id].set_label("Computer");
    }
    else {
        playerTypes[id].set_label("Human");
    }
}

// performs rage quit
void ControlFrame::on_ragequit_click() {
    gc_->setHintRequestedFlag(false);

	// requests controller to ask model to rage quit
    if (gc_->gameInProgress() && !g_->gameDone()) {
        int id = g_->getCurrentPlayerId();
        on_player_type_click(id);
        gc_->rageQuit();
    }
}

/// requests controller to ask model for a hint
void ControlFrame::on_hint_click() {
    if (gc_->gameInProgress() && !g_->gameDone()) {
        gc_->setHintRequestedFlag(true);
        g_->makeHintRequest();
    }
}
