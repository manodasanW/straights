#include <gtkmm/main.h>
#include "GameController.h"
#include "GameWindow.h"

int main(int argc, char* argv[])
{
	Gtk::Main kit(argc, argv);
    GameController gc;
	GameWindow window(gc);
	Gtk::Main::run(window);

	return 0;
}
