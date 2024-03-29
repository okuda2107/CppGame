CC = g++
WIN_CC = x86_64-w64-mingw32-g++
SRCS = $(wildcard ./src/*.cpp)
OBJS = $(patsubst ./src/%.cpp, ./obj/%.obj, $(SRCS))
TARGET = game
INCLUDE_PATH=-I/usr/include/SDL2 -I/usr/include/SOIL -I/usr/include/GL -I/usr/include/AL -I/usr/include/rapidjson -I/workspace/inc
LIBRARY_PATH=-L/usr/lib/x86_64-linux-gnu
LIBS = -lSDL2 -lSDL2_image -lSOIL -lGL -lGLEW

./obj/%.obj: ./src/%.cpp
	$(CC) -o $@ -c $< $(INCLUDE_PATH) 
$(TARGET): $(OBJS)
	$(CC) -o $@ $^ $(LIBS) $(LIBRARY_PATH)

clean:
	rm -f obj/*

win: $(TARGET).exe
	$(WIN_CC) -o $@ $(OBJS)
