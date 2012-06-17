CXX = g++ 			
CXXFLAGS = -g -Wall -MMD
OBJECTS = Card.o Command.o Role.o AIRole.o HumanRole.o Player.o main.o Deck.o
DEPENDS = ${OBJECTS:.o=.d}
EXEC = straights

${EXEC} : ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

clean :
	rm -rf ${DEPENDS} ${OBJECTS} ${EXEC}

-include ${DEPENDS}	# reads the .d files and reruns dependencies
