CXX := g++
TARGET := program

CXXFLAGS := -Wall -Wextra -std=c++20 -Iinclude -g -fsanitize=address
LDFLAGS := -fsanitize=address

SRC := $(shell find src -type f -name '*.cpp')
OBJ := $(SRC:.cpp=.o)

$(TARGET): $(OBJ)
	$(CXX) $(OBJ) $(LDFLAGS) -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

re: clean
	$(MAKE) $(TARGET)

.PHONY: clean re
