CC = g++ -g

l10e4: ex1.o
	$(CC) -o $@ $^

ex1.o: ex1.cpp compiler.hpp
	$(CC) -c -o $@ $<