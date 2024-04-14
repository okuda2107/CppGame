TARGET = game

CC = g++
SRCS = $(wildcard ./src/*.cpp)
OBJS = $(patsubst ./src/%.cpp, ./obj/%.obj, $(SRCS))
INCLUDE_PATH=-I/usr/include/SDL2 -I/usr/include/SOIL -I/usr/include/GL -I/usr/include/AL -I/usr/include/rapidjson -I/workspace/inc
LIBRARY_PATH=-L/usr/lib/x86_64-linux-gnu
LIBS = -lSDL2 -lSDL2_image -lSOIL -lGL -lGLEW

WIN_CC = i686-w64-mingw32-g++
WIN_OBJS = $(patsubst ./src/%.cpp, ./obj/%.winobj, $(SRCS))
WIN_INCLUDE_PATH=-I/workspace/External/SDL/include/SDL -I/usr/include/SOIL -I/usr/include/GL -I/usr/include/AL -I/usr/include/rapidjson -I/workspace/inc
WIN_LIBRARY_PATH=-L/workspace/External/SDL/lib/win/x86 -L/workspace/External/SOIL/lib/win/x86 -L/workspace/External/GLEW/lib/win/x86
WIN_LIBS = -lSDL2 -lSDL2_image -lSOIL -lglew32

$(TARGET): $(OBJS)
	$(CC) -o $@ $^ $(LIBS) $(LIBRARY_PATH)
./obj/%.obj: ./src/%.cpp
	$(CC) -o $@ -c $< $(INCLUDE_PATH) 

clean:
	rm -f obj/*

win: $(TARGET).exe
$(TARGET).exe: $(WIN_OBJS)
	$(WIN_CC) -o $@ $^ $(WIN_LIBS) $(WIN_LIBRARY_PATH)
./obj/%.winobj: ./src/%.cpp
	$(WIN_CC) -o $@ -c $< $(WIN_INCLUDE_PATH)
