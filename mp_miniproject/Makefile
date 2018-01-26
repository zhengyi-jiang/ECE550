SOURCES=myShell.cpp
OBJS=$(patsubst %.cpp, %.o, $(SOURCES))
CPPFLAGS=-ggdb3 -Wall -Werror -pedantic -std=gnu++98

myShell: $(OBJS)
	g++ $(CPPFLAGS) -o myShell $(OBJS)
%.o: %.cpp myShell.h
	g++ $(CPPFLAGS) -c $<

clean:
	rm myShell *~ *.o
