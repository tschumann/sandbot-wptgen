CPP = g++
CPPFLAGS = -O3 -g -march=core2 -mfpmath=sse \
           -Wall -Wextra

ALL:	sandbot-wptgen

WPTGEN_OBJ = main.o bspfile.o cmdlib.o config.o \
	mathlib.o scriplib.o trace.o waypoint.o world.o

sandbot-wptgen: ${WPTGEN_OBJ}
	${CPP} -g -o $@ ${WPTGEN_OBJ} -lstdc++ -lm

clean:
	-rm -f *.o
	-rm -f sandbot-wptgen

%.o:    %.cpp
	${CPP} ${CPPFLAGS} -c $< -o $@

%.o:    %.c
	${CPP} ${CPPFLAGS} -c $< -o $@
