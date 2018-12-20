test:
	g++ test.cpp tape.cpp -O2 -std=c++11 -pedantic-errors -o test

run:
	./test

clean:
	rm test