CXX = g++
CXXFLAGS = --std=c++17 -I .

BIN = ./bin
OBJ = $(BIN)/obj
DIRECTORIES = $(BIN) $(OBJ)

VPATH = ./examples

%: %.cpp matrix.o 
	$(CXX) $(CXXFLAGS) $< $(OBJ)/matrix.o -o ./bin/$@.out

matrix.o: matrix.cpp directories
	$(CXX) $(CXXFLAGS) matrix.cpp -c -o $(OBJ)/matrix.o

directories:
	mkdir -p $(DIRECTORIES)

.PHONY: clean
clean:
	rm -rf $(DIRECTORIES)