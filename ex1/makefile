# @author Shay Gali
# @link shay.gali@msmail.ariel.ac.il

CXX=clang++-9
CXXFLAGS=-std=c++2a -g -Werror -Wsign-conversion # c++20
VALGRIND_FLAGS=-v --leak-check=full --show-leak-kinds=all  --error-exitcode=99


SOURCES=graph/Graph.cpp algorithms/Algorithms.cpp
OBJECTS=$(subst .cpp,.o,$(SOURCES)) # replace .cpp with .o in SOURCES
TESTS_SOURCES=tests/test.cpp tests/TestCounter.cpp

.PHONY: run valgrind tidy clean test graph algorithms

PROG=main

run: $(PROG) graph algorithms
	./$<


$(PROG): $(PROG).o $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $@

test: 
	make -C tests test

valgrind: $(PROG)
	valgrind --tool=memcheck $(VALGRIND_FLAGS) ./$< 2>&1 | { egrep "lost| at " || true; }
	make -C tests valgrind

tidy:
	clang-tidy $(SOURCES) $(TESTS_SOURCES) -checks=bugprone-*,clang-analyzer-*,cppcoreguidelines-*,performance-*,portability-*,readability-*,-cppcoreguidelines-pro-bounds-pointer-arithmetic,-cppcoreguidelines-owning-memory --warnings-as-errors=-* --

graph:
	make -C graph all


algorithms:
	make -C algorithms all


%.o: %.cpp 
	$(CXX) $(CXXFLAGS) --compile $< -o $@

clean:
	make -C graph clean
	make -C algorithms clean
	make -C tests clean
	rm -f *.o test core main