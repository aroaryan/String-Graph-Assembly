CXX=clang++
INCLUDES=-Iincludes/
CXXFLAGS=-std=c++20 -gdwarf-4 -fstandalone-debug -Wall -Wextra -Werror -pedantic $(INCLUDES)

exec: bin/exec
tests: bin/tests

bin/exec: ./main.cpp ./code/readFile.cpp ./code/debruijn.cpp ./code/fmindex.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

bin/tests: ./tests.cpp ./code/readFile.cpp ./code/debruijn.cpp ./code/fmindex.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

.DEFAULT_GOAL := tests
.PHONY: clean exec tests

clean:
	rm -fr bin/* obj/*
