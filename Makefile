CXX = g++
CXXFLAGS = -Wall -std=c++11

SRC = main.cpp Graph.cpp Algorithms.cpp Queue.cpp PriorityQueue.cpp UnionFind.cpp
OBJ = $(SRC:.cpp=.o)
TARGET = main.out
TEST_SRC = test.cpp
TEST_TARGET = test.out

all: Main

Main: $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(TARGET)

test: $(OBJ) $(TEST_SRC)
	$(CXX) $(CXXFLAGS) $(OBJ) $(TEST_SRC) -o $(TEST_TARGET)

valgrind: Main
	valgrind --leak-check=full ./$(TARGET)

clean:
	rm -f *.o *.out
