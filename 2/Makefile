all: test_run

callback:
	g++ -c callback.cpp -o callback.o

test_run : callback test
	g++ callback.o test.o -o prog
	./prog

test:
	g++ -c test.cpp -o test.o