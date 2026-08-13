CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++20 -Iinclude

TARGET = program

SRC = $(shell find src -name "*.cpp")
OBJ = $(SRC:.cpp=.o)

$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $(TARGET)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

re: clean $(TARGET)

.PHONY: clean re
