#ifndef CONTROL_FRAME
#define CONTROL_FRAME

#include <gtkmm.h>

#include "GameController.h"
#include "Game.h"
#include "Observer.h"

class ControlFrame : public Observer {

public:
	ControlFrame(GameController *, Game *);
    virtual ~ControlFrame();
	void notify();
    
protected:
    void on_start_click();
    void on_end_click();
    
    void on_player_type_click(int);
    
private:
    
    GameController *gc_;
    Game *g_;
    
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
    bool playerTypeBools[4];
    Gtk::Button playerTypes[4];
};

#endif
