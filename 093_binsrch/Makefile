test:test-bsearch.o search.o
	g++ -o test test-bsearch.o search.o
t.o:test-bsearch.cpp
	g++  -Wall -Werror -std=gnu++98 -pedantic -c test-bsearch.cpp
s.o:search.cpp
	g++  -Wall -Werror -std=gnu++98 -pedantic -c search.cpp
clean:
	rm *.o *~

