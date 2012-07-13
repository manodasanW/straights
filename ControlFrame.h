#ifndef CONTROL_FRAME
#define CONTROL_FRAME

#include <gtkmm/box.h>
#include <gtkmm/button.h>
#include <gtkmm/label.h>
#include <gtkmm/entry.h>
#include <gtkmm/frame.h>

#include "GameController.h"
#include "Game.h"
#include "Observer.h"

class ControlFrame : public Observer {

public:
	ControlFrame(GameController *, Game *);			// constructor
    virtual ~ControlFrame();						// destructor
	void notify();									// updates view
    
protected:
    void on_start_click();							// click button clicked
    void on_end_click();							// end button clicked
    
    void on_player_type_click(int);					// updates on button for Human/AI click
    void on_ragequit_click();						// rage quit button cliked
    void on_hint_click();							// hint button clicked
    
private:
    
    GameController *gc_;							// controller - handles input events
    Game *g_;										// facade - used to get certain information from model
    bool playerTypeBools[4];						// stores whether player is a AI or human based on button
    
	// GUI elements
    Gtk::VBox controlArea;
    
    Gtk::Frame mainControlFrame;
    Gtk::VBox mainControl;
    Gtk::HBox mainButtons;
    Gtk::Button startButton;
    Gtk::Button endButton;
    Gtk::HBox seedEntryControl;
    Gtk::Label seedEntryLabel;
    Gtk::Entry seedEntry;
    
    Gtk::Frame playerControlFrame;
    Gtk::VBox playerControl;
    Gtk::Label currentPlayer;
    Gtk::HBox playerControlButtons;
    Gtk::Button rageButton;
    Gtk::Button hintButton;
    
    Gtk::Frame statsControlFrame;
    Gtk::VBox statsControl;
    Gtk::HBox playerInfoBoxes[4];
    Gtk::Label playerInfoLabels[4];
    Gtk::Label playerScores[4];
    Gtk::Button playerTypes[4];
};

#endif /* CONTROL_FRAME */
