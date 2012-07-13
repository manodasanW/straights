#include <gtkmm/main.h>
#include "GameController.h"
#include "GameWindow.h"
#include "Game.h"

int main(int argc, char* argv[])
{
	Gtk::Main kit(argc, argv);
    Game g;
    GameController gc(&g);
	GameWindow window(&gc, &g);
	Gtk::Main::run(window);

	return 0;
}
