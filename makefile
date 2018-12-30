test:
	g++ test.cpp tape.cpp -O2 -std=c++11 -pedantic-errors -o test

example:
	g++ example.cpp tape.cpp -O2 -std=c++11 -o example
	./example
	rm example

run:
	./test

clean:
	rm test