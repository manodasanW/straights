CXX = g++ 			
CXXFLAGS = -g -Wall `pkg-config gtkmm-2.4 --cflags --libs`
OBJECTS = Game.o Player.o Role.o AIRole.o HumanRole.o Card.o CardList.o Deck.o Subject.o GameController.o DeckGUI.o PlayFrame.o ControlFrame.o GameWindow.o main.o
DEPENDS = ${OBJECTS:.o=.d}
EXEC = straights

${EXEC} : ${OBJECTS}
	${CXX} ${OBJECTS} ${CXXFLAGS} -o ${EXEC}

clean :
	rm -rf ${DEPENDS} ${OBJECTS} ${EXEC}

-include ${DEPENDS}
