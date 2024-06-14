ifeq ($(OS), Windows_NT)
	TARGET = main.exe
else
	TARGET = main
endif

CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2

SOURCES = $(wildcard src/*.cpp)

OBJECTS = $(patsubst src/%.cpp,obj/%.o,$(SOURCES))

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

obj/%.o: src/%.cpp | obj
	$(CXX) $(CXXFLAGS) -c $< -o $@

obj:
	mkdir obj