#ifndef CONTROL_FRAME
#define CONTROL_FRAME

#include <gtkmm.h>

class ControlFrame : public Gtk::Frame {

public:
	ControlFrame();
	virtual ~ControlFrame();

private:
    Gtk::VBox controlArea;
    
    Gtk::HBox mainControl;
    Gtk::Button startButton;
    Gtk::Button endButton;
    
    Gtk::HBox seedEntryControl;
    Gtk::Label *seedEntryLabel;
    Gtk::Entry seedEntry;
};

#endif
