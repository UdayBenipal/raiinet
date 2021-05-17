CXX = g++
CXXFLAGS = -std=c++14 -MMD -Werror=vla
EXEC = RAIInet
OBJECTS = basiclink.o cell.o firewall.o graphicsdisplay.o linkpolarize.o player.o scan.o window.o boost.o download.o game.o linkboost.o main.o polarize.o textdisplay.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} -lX11 -L/usr/X11/lib -I/usr/X11/include 

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
