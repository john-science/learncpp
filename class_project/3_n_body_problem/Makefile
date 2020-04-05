CPP=g++
CPPFLAGS=-O3
RM=rm -f

SRCS=main.cpp universe.cpp newtonian_dynamics.cpp
OBJS=$(subst .cpp,.o,$(SRCS))

all: nbody

nbody: $(OBJS)
	$(CPP) -o nbody $(OBJS)

%.o: %.cpp
	$(CPP) -c $(CPPFLAGS) $<

clean:
	$(RM) $(OBJS)
	$(RM) nbody

distclean: clean

