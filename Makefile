ifeq ($(OS), Windows_NT)
	TARGET = main.exe
	RM = del /q
	SLASH = \\
else
	TARGET = main
	SLASH = /
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
	-$(RM) *.tmp

SORTS = bubble-sort counting-sort heap-sort insertion-sort merge-sort quick-sort selection-sort
INPUT_SIZES = 10000 30000 50000 100000 300000 500000
OUTPUTS = $(foreach size,$(INPUT_SIZES),$(foreach sort,$(SORTS),benchmarks/$(sort)-$(size).txt))

define AddBenchmark
benchmarks/$(1)-$(2).txt: | benchmarks $(TARGET)
	-$(RM) "benchmarks$(SLASH)$(1)-$(2).txt"
	$(TARGET) -a $(1) $(2) -both > bench-$(1)-$(2).tmp
	rename bench-$(1)-$(2).tmp "benchmarks/$(1)-$(2).txt"
endef

$(foreach sort,$(SORTS),$(foreach size,$(INPUT_SIZES),$(eval $(call AddBenchmark,$(sort),$(size)))))

benchmarks:
	mkdir benchmarks

benchmark: $(OUTPUTS)

.PHONY: all debug clean benchmark
