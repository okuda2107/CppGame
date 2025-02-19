cd /workspace/exlibs

# if [ ! -d "vcpkg" ]; then
#     git clone https://github.com/microsoft/vcpkg
#     cd vcpkg
#     ./bootstrap-vcpkg.sh
# fi

if [ ! -d "SDL2-2.32.0" ]; then
    curl -fsSL "https://github.com/libsdl-org/SDL/releases/download/release-2.32.0/SDL2-devel-2.32.0-mingw.tar.gz" | tar -xz
fi

if [ ! -d "SDL2_image-2.8.5" ]; then
    curl -fsSL "https://github.com/libsdl-org/SDL_image/releases/download/release-2.8.5/SDL2_image-devel-2.8.5-mingw.tar.gz" | tar -xz
fi

if [ ! -d "SDL2_mixer-2.8.1" ]; then
    curl -fsSL "https://github.com/libsdl-org/SDL_mixer/releases/download/release-2.8.1/SDL2_mixer-devel-2.8.1-mingw.tar.gz" | tar -xz
fi

if [ ! -d "SDL2_net-2.2.0" ]; then
    curl -fsSL "https://github.com/libsdl-org/SDL_net/releases/download/release-2.2.0/SDL2_net-devel-2.2.0-mingw.tar.gz" | tar -xz
fi

if [ ! -d "SDL2_ttf-2.24.0" ]; then
    curl -fsSL "https://github.com/libsdl-org/SDL_ttf/releases/download/release-2.24.0/SDL2_ttf-devel-2.24.0-mingw.tar.gz" | tar -xz
fi
