CXX = g++ 			
CXXFLAGS = -g -Wall -MMD
OBJECTS = main.o AIRole.o Card.o Command.o Deck.o HumanRole.o Player.o Role.o
DEPENDS = ${OBJECTS:.o=.d}
EXEC = straights

${EXEC} : ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

clean :
	rm -rf ${DEPENDS} ${OBJECTS} ${EXEC}

-include ${DEPENDS}	# reads the .d files and reruns dependencies
