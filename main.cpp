#include <gtkmm/main.h>
#include "GameController.h"
#include "GameWindow.h"
#include "Game.h"

// main function
int main(int argc, char* argv[])
{
	// sets up GTK, and displays the main window
	Gtk::Main kit(argc, argv);
    Game g;
    GameController gc(&g);
	GameWindow window(&gc, &g);
	Gtk::Main::run(window);

	return 0;
}
