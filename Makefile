ifeq ($(OS), Windows_NT)
	TARGET = main.exe
	RM = del /q
else
	TARGET = main
endif

CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2

SOURCES = $(wildcard src/*.cpp)

OBJECTS = $(patsubst src/%.cpp,obj/%.o,$(SOURCES))

all: CXXFLAGS += -DNDEBUG
all: $(TARGET)

debug: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

obj/%.o: src/%.cpp | obj
	$(CXX) $(CXXFLAGS) -c $< -o $@

obj:
	mkdir obj

clean:
	-$(RM) obj
	-$(RM) $(TARGET)