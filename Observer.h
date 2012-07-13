/*
 Observer.h
 
 Declaration of Observer class.
 */

#ifndef _OBSERVER_H_
#define _OBSERVER_H_

#include <gtkmm/frame.h>

class Observer : public Gtk::Frame {

public:
    virtual ~Observer() {}
	virtual void notify() = 0;

};

#endif

