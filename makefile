CXX      = g++
CXXFLAGS = -std=c++17 -Wall -Wextra
SDL_FLAGS = $(shell sdl2-config --cflags --libs)
TARGET   = Paint
SRCS     = $(wildcard src/*.cpp)
OBJS     = $(patsubst src/%.cpp,build/%.o,$(SRCS))

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(SDL_FLAGS)

build/%.o: src/%.cpp
	mkdir -p build
	$(CXX) $(CXXFLAGS) $(SDL_FLAGS) -c $< -o $@

clean:
	rm -rf build $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run