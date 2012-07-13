/*
 Observer.h
 
 Declaration of Observer class.
 */

#ifndef _OBSERVER_H_
#define _OBSERVER_H_

#include <gtkmm/frame.h>

// class used to store all gui elements which require update to changes in the model
class Observer : public Gtk::Frame {

public:
    virtual ~Observer() {}			// destructor
	virtual void notify() = 0;		// function to call when there is update

};

#endif /* _OBSERVER_H_ */
