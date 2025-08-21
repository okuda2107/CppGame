set(CMAKE_C_COMPILER   "C:/msys64/mingw64/bin/gcc.exe")
set(CMAKE_CXX_COMPILER "C:/msys64/mingw64/bin/g++.exe")

set(CMAKE_INCLUDE_PATH
    "${CMAKE_SOURCE_DIR}/exlibs/SDL2-2.32.8//x86_64-w64-mingw32/include/SDL2"
    "${CMAKE_SOURCE_DIR}/exlibs/SDL2_image-2.8.8/x86_64-w64-mingw32/include/SDL2"
    "${CMAKE_SOURCE_DIR}/exlibs/SDL2_mixer-2.8.1/x86_64-w64-mingw32/include/SDL2"
    "${CMAKE_SOURCE_DIR}/exlibs/glew-2.2.0/include/GL"
    "${CMAKE_SOURCE_DIR}/exlibs/rapidjson/include/rapidjson"
    "${CMAKE_SOURCE_DIR}/exlibs/rapidjson/include"
    "${CMAKE_SOURCE_DIR}/exlibs/Simple-OpenGL-Image-Library/src"
    "${CMAKE_SOURCE_DIR}/exlibs/openal-soft-1.24.3-bin/include/AL"
    "${CMAKE_SOURCE_DIR}/exlibs/openal-soft-1.24.3-bin/include"
    "${CMAKE_SOURCE_DIR}/exlibs/freealut/include/AL"
)

set(CMAKE_LIBRARY_PATH
    "${CMAKE_SOURCE_DIR}/exlibs/SDL2-2.32.8/x86_64-w64-mingw32/lib"
    "${CMAKE_SOURCE_DIR}/exlibs/SDL2_image-2.8.8/x86_64-w64-mingw32/lib"
    "${CMAKE_SOURCE_DIR}/exlibs/SDL2_mixer-2.8.1/x86_64-w64-mingw32/lib"
    "${CMAKE_SOURCE_DIR}/exlibs/SDL2_net-2.2.0/x86_64-w64-mingw32/lib"
    "${CMAKE_SOURCE_DIR}/exlibs/SDL2_ttf-2.24.0/x86_64-w64-mingw32/lib"
    "${CMAKE_SOURCE_DIR}/exlibs/glew-2.2.0/build/lib"
    "${CMAKE_SOURCE_DIR}/exlibs/Simple-OpenGL-Image-Library/build"
    "${CMAKE_SOURCE_DIR}/exlibs/openal-soft-1.24.3-bin/libs/Win64"
    "${CMAKE_SOURCE_DIR}/exlibs/freealut/build/src"
)

set(CMAKE_EXECUTABLE_SUFFIX ".exe")

set(SDL2_LIBRARY
    mingw32
    SDL2main
    SDL2
)

set(OPENGL_LIBRARY
    OPENGL32
    GLEW32
)

set(OPENAL_LIBRARY
    OpenAL32
    alut
)

set(DLL_FILES
    "${CMAKE_SOURCE_DIR}/exlibs/SDL2-2.32.8/x86_64-w64-mingw32/bin/SDL2.dll"
    "${CMAKE_SOURCE_DIR}/exlibs/SDL2_mixer-2.8.1/x86_64-w64-mingw32/bin/SDL2_mixer.dll"
    "${CMAKE_SOURCE_DIR}/exlibs/glew-2.2.0/build/bin/glew32.dll"
    "${CMAKE_SOURCE_DIR}/exlibs/openal-soft-1.24.3-bin/bin/Win64/soft_oal.dll"
    "${CMAKE_SOURCE_DIR}/exlibs/openal-soft-1.24.3-bin/router/Win64/OpenAL32.dll"
    "${CMAKE_SOURCE_DIR}/exlibs/freealut/build/src/libalut.dll"
)
