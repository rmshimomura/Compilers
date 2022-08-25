CC = g++ -g

l5e2: ex2.o
	$(CC) -o $@ $^

ex2.o: ex2.cpp compiler.hpp
	$(CC) -c -o $@ $<