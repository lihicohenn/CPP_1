#lihicohen1123@gmail.com
C=g++ -std=c++11
HEADERS=Edge.hpp Graph.hpp Queue.hpp Algorithms.hpp UnionFind.hpp PriorityQueue.hpp
Target=main
TEST_TARGET=Test
FLAGS=-c -g -Wall
OBJECT=Graph.o main.o Queue.o Algorithms.o UnionFind.o PriorityQueue.o
TEST_OBJ=Graph.o Queue.o Algorithms.o UnionFind.o PriorityQueue.o test.o

$(Target):$(OBJECT)
	$(C) -Wall -o $(Target) $(OBJECT)
$(TEST_TARGET):$(TEST_OBJ)
	$(C) -Wall -o $(TEST_TARGET) $(TEST_OBJ)


Graph.o:Graph.cpp $(HEADERS)
	$(C) $(FLAGS) Graph.cpp
Queue.o:Queue.cpp $(HEADERS)
	$(C) $(FLAGS) Queue.cpp
PriorityQueue.o: PriorityQueue.cpp $(HEADERS)
	$(C) $(FLAGS) PriorityQueue.cpp
Algorithms.o:Algorithms.cpp $(HEADERS)
	$(C) $(FLAGS) Algorithms.cpp
UnionFind.o:UnionFind.cpp $(HEADERS)
	$(C) $(FLAGS) UnionFind.cpp
main.o:main.cpp $(HEADERS)
	$(C) $(FLAGS) main.cpp

test.o:test.cpp $(HEADERS)
	$(C) $(FLAGS) test.cpp


run_tests:$(TEST_TARGET)
	./$(TEST_TARGET)


valgrind:$(Target)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(Target)

valgrind_tests:$(TEST_TARGET)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(TEST_TARGET)

.PHONY:$(Target) clean

clean: 
	rm -f *.o $(Target) $(TEST_TARGET)