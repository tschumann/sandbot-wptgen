CPP = g++
CPPFLAGS = -std=c++14 -march=core2 -mfpmath=sse -Wall -Wextra -fno-math-errno

ALL: sandbot-wptgen

WPTGEN_OBJ = main.o bspfile.o cmdlib.o logger.o map.o \
	mathlib.o maths.o scriplib.o trace.o util.o waypoint.o world.o

# links the objects
DO_BUILD = ${CPP} -g -o sandbot-wptgen ${WPTGEN_OBJ} -lstdc++ -lm

sandbot-wptgen:CPPFLAGS += -g -O3
sandbot-wptgen: ${WPTGEN_OBJ}
	${DO_BUILD}

test-gprof: CPPFLAGS += -g3 -O0
test-gprof: ${WPTGEN_OBJ}
	${DO_BUILD}

test-ubsan: CPPFLAGS += -g -O3
test-ubsan: ${WPTGEN_OBJ}
	${DO_BUILD} -fsanitize=undefined -fsanitize=address

clean:
	-rm -f *.o
	-rm -f sandbot-wptgen

%.o:    %.cpp
	${CPP} ${CPPFLAGS} -c $< -o $@

%.o:    %.c
	${CPP} ${CPPFLAGS} -c $< -o $@

