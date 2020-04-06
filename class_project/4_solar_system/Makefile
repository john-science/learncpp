CPP=g++
CPPFLAGS=-O3
RM=rm -f

SRCS=main.cpp universe.cpp newtonian_dynamics.cpp
OBJS=$(subst .cpp,.o,$(SRCS))

all: system

system: $(OBJS)
	$(CPP) -o system $(OBJS)

%.o: %.cpp
	$(CPP) -c $(CPPFLAGS) $<

clean:
	$(RM) $(OBJS)
	$(RM) system

distclean: clean

