CC = g++
SRCS = $(wildcard ./src/*.cpp)
OBJS = $(patsubst ./src/%.cpp, ./obj/%.obj, $(SRCS))
TARGET = game
INCLUDE_PATH=/usr/include/SOIL:/usr/include/GL:/usr/include/rapidjson:/workspace/inc
LIBRARY_PATH=/usr/lib/x86_64-linux-gnu
LIBS = -lSDL2 -lSDL2_image -lSOIL -lGL -lGLEW

./obj/%.obj: ./src/%.cpp
	$(CC) -o $@ -c $< -I$(INCLUDE_PATH) 
$(TARGET): $(OBJS)
	$(CC) -o $@ $^ $(LIBS) -L$(LIBRARY_PATH)

clean:
	rm -f obj/*
