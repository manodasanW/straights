#include "ControlFrame.h"
#include <string>
#include <sstream>

using namespace std;

ControlFrame::ControlFrame(GameController *gc, Game *g)
    : Observer(), gc_(gc), g_(g), controlArea(false, 10), mainControlFrame("Game Controls"), mainControl(true, 10),
    mainButtons(true, 10), startButton("Start Game"), endButton("End Game"), seedEntryControl(false, 10),
    seedEntryLabel("Seed:"), playerControlFrame("Player Controls"), playerControl(false, 10),
    currentPlayer("Current Player: 1"), playerControlButtons(true, 10), rageButton("Ragequit"),
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
        stringstream ss;
        ss << (i+1);
        playerInfoLabels[i].set_label(std::string("Player " + ss.str()).c_str());
        playerScores[i].set_label("Score: 0");
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
    endButton.set_sensitive(false);
    
    // finally, add each major part of the control frame
    controlArea.add(mainControlFrame);
    controlArea.add(playerControlFrame);
    controlArea.add(statsControlFrame);
    add(controlArea);
}

ControlFrame::~ControlFrame() {
}

void ControlFrame::notify()
{

}

void ControlFrame::on_start_click() {
    if (!gc_->gameInProgress()) {
        for (int i = 0; i < 4; i++) {
            playerInfoBoxes[i].remove(playerTypes[i]);
            playerInfoBoxes[i].add(playerScores[i]);
        }
    }
    startButton.set_sensitive(false);
    endButton.set_sensitive(true);
    
    show_all();
    
    string seed_str = seedEntry.get_text();
    istringstream buffer(seed_str);
    int seed;
    if (!(buffer >> seed)) {
        seed = 0;
    }
    gc_->startGame(seed, playerTypeBools);
}

void ControlFrame::on_end_click() {
    if (gc_->gameInProgress()) {
        for (int i = 0; i < 4; i++) {
            playerInfoBoxes[i].remove(playerScores[i]);
            playerInfoBoxes[i].add(playerTypes[i]);
        }
    }
    startButton.set_sensitive(true);
    endButton.set_sensitive(false);
    
    show_all();
    gc_->endGame();
}

void ControlFrame::on_player_type_click(int id) {
    playerTypeBools[id] = !playerTypeBools[id];
    if (playerTypeBools[id]) {
        playerTypes[id].set_label("Computer");
    }
    else {
        playerTypes[id].set_label("Human");
    }
}
