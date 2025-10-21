get_filename_component(TOOLCHAIN_DIR "${CMAKE_TOOLCHAIN_FILE}" DIRECTORY)
set(ROOT_DIR "${TOOLCHAIN_DIR}/..")

set(CMAKE_C_COMPILER   "C:/msys64/mingw64/bin/gcc.exe")
set(CMAKE_CXX_COMPILER "C:/msys64/mingw64/bin/g++.exe")

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_CXX_FLAGS} -static-libgcc -static-libstdc++")

set(CMAKE_INCLUDE_PATH
    "${ROOT_DIR}/exlibs/SDL2-2.32.8/x86_64-w64-mingw32/include/SDL2"
    "${ROOT_DIR}/exlibs/SDL2_image-2.8.8/x86_64-w64-mingw32/include/SDL2"
    "${ROOT_DIR}/exlibs/SDL2_mixer-2.8.1/x86_64-w64-mingw32/include/SDL2"
    "${ROOT_DIR}/exlibs/SDL2_ttf-2.24.0/x86_64-w64-mingw32/include/SDL2"
    "${ROOT_DIR}/exlibs/glew-2.2.0/include/GL"
    "${ROOT_DIR}/exlibs/rapidjson/include/rapidjson"
    "${ROOT_DIR}/exlibs/rapidjson/include"
    "${ROOT_DIR}/exlibs/Simple-OpenGL-Image-Library/src"
    "${ROOT_DIR}/exlibs/openal-soft-1.24.3-bin/include/AL"
    "${ROOT_DIR}/exlibs/openal-soft-1.24.3-bin/include"
    "${ROOT_DIR}/exlibs/freealut/include/AL"
)

set(CMAKE_LIBRARY_PATH
    "${ROOT_DIR}/exlibs/SDL2-2.32.8/x86_64-w64-mingw32/lib"
    "${ROOT_DIR}/exlibs/SDL2_image-2.8.8/x86_64-w64-mingw32/lib"
    "${ROOT_DIR}/exlibs/SDL2_mixer-2.8.1/x86_64-w64-mingw32/lib"
    "${ROOT_DIR}/exlibs/SDL2_net-2.2.0/x86_64-w64-mingw32/lib"
    "${ROOT_DIR}/exlibs/SDL2_ttf-2.24.0/x86_64-w64-mingw32/lib"
    "${ROOT_DIR}/exlibs/glew-2.2.0/build/lib"
    "${ROOT_DIR}/exlibs/Simple-OpenGL-Image-Library/build"
    "${ROOT_DIR}/exlibs/openal-soft-1.24.3-bin/libs/Win64"
    "${ROOT_DIR}/exlibs/freealut/build/src"
)

set(CMAKE_EXECUTABLE_SUFFIX ".exe")

set(CMAKE_LIBRARIES
    "mingw32"
    "SDL2main"
    "SDL2"
    "SDL2_image"
    "SDL2_mixer"
    "SDL2_net"
    "SDL2_ttf"
    "SOIL"
    "OPENGL32"
    "GLEW32"
    "OpenAL32"
    "alut"
)

set(DLL_FILES
    "${ROOT_DIR}/exlibs/SDL2-2.32.8/x86_64-w64-mingw32/bin/SDL2.dll"
    "${ROOT_DIR}/exlibs/SDL2_mixer-2.8.1/x86_64-w64-mingw32/bin/SDL2_mixer.dll"
    "${ROOT_DIR}/exlibs/SDL2_ttf-2.24.0/x86_64-w64-mingw32/bin/SDL2_ttf.dll"
    "${ROOT_DIR}/exlibs/glew-2.2.0/build/bin/glew32.dll"
    "${ROOT_DIR}/exlibs/openal-soft-1.24.3-bin/bin/Win64/soft_oal.dll"
    "${ROOT_DIR}/exlibs/openal-soft-1.24.3-bin/router/Win64/OpenAL32.dll"
    "${ROOT_DIR}/exlibs/freealut/build/src/libalut.dll"
    "C:/msys64/mingw64/bin/libwinpthread-1.dll"
)
