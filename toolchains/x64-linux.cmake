get_filename_component(TOOLCHAIN_DIR "${CMAKE_TOOLCHAIN_FILE}" DIRECTORY)
set(ROOT_DIR "${TOOLCHAIN_DIR}/..")

set(CMAKE_INCLUDE_PATH
"/usr/include/SDL2"
"/usr/include/SOIL"
"/usr/include/GL"
"/usr/include/rapidjson"
"/usr/include/AL"
)

# set(CMAKE_LIBRARY_PATH
#     "${CMAKE_SOURCE_DIR}/exlibs/xxx""
# )

set(SDL2_LIBRARY
    SDL2
)

set(OPENGL_LIBRARY
    GL
    GLEW
)

set(OPENAL_LIBRARY
    openal
    alut
)

set(DLL_FILES
    "/usr/lib/x86_64-linux-gnu/libSDL2.so"
    "/usr/lib/x86_64-linux-gnu/libalut.so"
)
