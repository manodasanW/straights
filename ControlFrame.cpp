#include "ControlFrame.h"

ControlFrame::ControlFrame() : controlArea(false, 10), mainControl(true, 10),
    startButton("Start Game"), endButton("End Game"), seedEntryControl(false, 10),
    seedEntryLabel(new Gtk::Label("Seed:"))
{
    mainControl.add(startButton);
    mainControl.add(endButton);
    
    seedEntry.set_max_length(9);
    //seedEntryControl.add(seedEntryLabel);
    seedEntryControl.add(seedEntry);
    
    controlArea.add(mainControl);
    controlArea.add(seedEntryControl);
    add(controlArea);
}

ControlFrame::~ControlFrame() {
    //delete seedEntryLabel;
}
