CPP=g++
RM=rm -f

SRCS=main.cpp universe.cpp
OBJS=$(subst .cpp,.o,$(SRCS))

all: nbody

nbody: $(OBJS)
	$(CPP) -o nbody $(OBJS)

%.o: %.cpp
	$(CPP) -c $<

clean:
	$(RM) $(OBJS)
	$(RM) nbody

distclean: clean

