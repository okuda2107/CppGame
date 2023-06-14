CC = g++
SRCS = $(wildcard ./src/*.cpp)
OBJS = $(patsubst ./src/%.cpp, ./obj/%.obj, $(SRCS))
LIBS = -lSDL2 -lSDL2_image -lSOIL -lGL -lGLEW 
TARGET = game

./obj/%.obj: ./src/%.cpp
	$(CC) -o $@ -c $< 
$(TARGET): $(OBJS)
	$(CC) -o $@ $^ $(LIBS)

clean:
	rm obj/*
