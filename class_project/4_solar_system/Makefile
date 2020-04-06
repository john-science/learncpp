CPP=g++
CPPFLAGS=-O3
RM=rm -f

SRCS=main.cpp universe.cpp newtonian_dynamics.cpp
OBJS=$(subst .cpp,.o,$(SRCS))

all: ssystem

ssystem: $(OBJS)
	$(CPP) -o ssystem $(OBJS)

%.o: %.cpp
	$(CPP) -c $(CPPFLAGS) $<

clean:
	$(RM) $(OBJS)
	$(RM) ssystem

distclean: clean

