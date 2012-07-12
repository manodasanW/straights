#include "ControlFrame.h"
#include <string>
#include <sstream>

ControlFrame::ControlFrame() 
	:Observer(), controlArea(false, 10), mainControlFrame("Game Controls"), mainControl(true, 10),
    mainButtons(true, 10),
    startButton("Start Game"), endButton("End Game"), seedEntryControl(false, 10),
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
        std::stringstream ss;
        ss << (i+1);
        playerInfoLabels[i].set_label(std::string("Player " + ss.str()).c_str());
        playerScores[i].set_label("Score: 0");
        playerTypes[i].set_label("Human");
        playerInfoBoxes[i].add(playerInfoLabels[i]);
        playerInfoBoxes[i].add(playerTypes[i]);
        statsControl.add(playerInfoBoxes[i]);
    }
    statsControlFrame.add(statsControl);
    
    // finally, add each major part of the control frame
    controlArea.add(mainControlFrame);
    controlArea.add(playerControlFrame);
    controlArea.add(statsControlFrame);
    add(controlArea);
}

void ControlFrame::notify()
{

}

ControlFrame::~ControlFrame() {
}
