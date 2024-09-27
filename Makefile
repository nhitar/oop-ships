SOURCES = $(wildcard sources/*.cpp)
OBJECTS = $(patsubst sources/%.cpp,sources/%.o,$(SOURCES))
CC = g++
CFLAGS = -Wall -Wextra -std=c++17
LDFLAGS = -lm

all: game

game: $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o game

sources/%.o : sources/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf sources/*.o game