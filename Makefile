CXX = g++ 			
CXXFLAGS = -g -Wall `pkg-config gtkmm-2.4 --cflags --libs`
OBJECTS = DeckGUI.o PlayFrame.o ControlFrame.o GameWindow.o main.o
DEPENDS = ${OBJECTS:.o=.d}
EXEC = straights

${EXEC} : ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

PlayFrame.o : DeckGUI.h

clean :
	rm -rf ${DEPENDS} ${OBJECTS} ${EXEC}

-include ${DEPENDS}
