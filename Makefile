CC = g++
SRCS = $(wildcard ./src/*.cpp)
OBJS = $(patsubst ./src/%.cpp, ./obj/%.obj, $(SRCS))
TARGET = game

./obj/%.obj: ./src/%.cpp
	$(CC) -o $@ -c $< 
$(TARGET): $(OBJS)
	$(CC) -o $@ $^
