CPP = g++
CPPFLAGS = -O3 -g -std=c++14 -march=core2 -mfpmath=sse -Wall -Wextra

ALL:	sandbot-wptgen

WPTGEN_OBJ = main.o bspfile.o cmdlib.o logger.o map.o \
	mathlib.o maths.o scriplib.o trace.o util.o waypoint.o world.o

sandbot-wptgen: ${WPTGEN_OBJ}
	${CPP} -g -o $@ ${WPTGEN_OBJ} -lstdc++ -lm

clean:
	-rm -f *.o
	-rm -f sandbot-wptgen

%.o:    %.cpp
	${CPP} ${CPPFLAGS} -c $< -o $@

%.o:    %.c
	${CPP} ${CPPFLAGS} -c $< -o $@
