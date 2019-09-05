CXX=g++
CXXFLAGS=-std=c++14 -Wextra -Wall -Werror -Werror=vla -MMD -g
OBJECTS= main.o command.o grid.o cell.o textdisplay.o graphicsdisplay.o block.o iblock.o jblock.o lblock.o oblock.o sblock.o tblock.o zblock.o subject.o window.o
DEPENDS=${OBJECTS:.o=.d}
EXEC=quadris

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} -lX11

-include ${DEPENDS}

clean:
	rm ${OBJECTS} ${DEPENDS} ${EXEC}
.PHONY: clean
