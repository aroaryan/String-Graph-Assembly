CXX=clang++
INCLUDES=-Iincludes/
CXXFLAGS=-std=c++20 -gdwarf-4 -fstandalone-debug -Wall -Wextra -Werror -pedantic $(INCLUDES)

exec: bin/exec
tests: bin/tests

bin/exec: ./main.cpp ./code/readFile.cpp ./code/debruijn.cpp 
	$(CXX) $(CXXFLAGS) $^ -o $@

bin/tests: ./tests/test.cpp ./code/readFile.cpp ./code/debruijn.cpp 
	$(CXX) $(CXXFLAGS) $^ -o $@

.DEFAULT_GOAL := exec
.PHONY: clean exec tests

clean:
	rm -fr bin/* obj/*
