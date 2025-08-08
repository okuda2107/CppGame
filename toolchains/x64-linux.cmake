# set(CMAKE_INCLUDE_PATH
#     "${CMAKE_SOURCE_DIR}/exlibs/SDL2-2.32.0/x86_64-w64-mingw32/include/SDL2"
#     "${CMAKE_SOURCE_DIR}/exlibs/SDL2_image-2.8.5/x86_64-w64-mingw32/include/SDL2"
#     "${CMAKE_SOURCE_DIR}/exlibs/glew-2.2.0/include/GL"
#     "/ust/include/GL"
#     "${CMAKE_SOURCE_DIR}/exlibs/rapidjson-1.1.0/include/rapidjson"
#     "${CMAKE_SOURCE_DIR}/exlibs/Simple-OpenGL-Image-Library/src"
# )

# set(CMAKE_LIBRARY_PATH
#     "${CMAKE_SOURCE_DIR}/exlibs/SDL2-2.32.0/x86_64-w64-mingw32/lib"
#     "${CMAKE_SOURCE_DIR}/exlibs/SDL2_image-2.8.5/x86_64-w64-mingw32/lib"
#     "${CMAKE_SOURCE_DIR}/exlibs/glew-2.2.0/build/lib"
#     "/ust/include/GL"
#     "${CMAKE_SOURCE_DIR}/exlibs/Simple-OpenGL-Image-Library/lib"
# )

set(CMAKE_INCLUDE_PATH
    "/usr/include/SDL2"
    "/usr/include/SOIL"
    "/usr/include/GL"
    "/usr/include/rapidjson"
)

set(SDL2_LIBRARY
    SDL2
)

set(OPENGL_LIBRARY
    GL
    GLEW
)

set(SDL2_DLL "/usr/lib/x86_64-linux-gnu/libSDL2.so")
set(GLEW_DLL "")
