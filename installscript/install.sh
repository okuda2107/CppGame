#!/bin/sh

sudo true
ROOT_DIR="$(cd "$(dirname "$0")" && cd .. && pwd)"

EXLIBS_DIR="$ROOT_DIR/exlibs"

install_command() {
    for command in "$@"; do
        if ! type "$command" > /dev/null 2>&1; then
            sudo apt update
            sudo apt install -y "$command"
        fi
    done
}

get_package_manager() {
    if type apt > /dev/null 2>&1; then
        echo "apt"
    elif type dnf > /dev/null 2>&1; then
        echo "dnf"
    elif type yum > /dev/null 2>&1; then
        echo "yum"
    elif type pacman > /dev/null 2>&1; then
        echo "pacman"
    elif type zypper > /dev/null 2>&1; then
        echo "zypper"
    else
        echo "unsupported"
    fi
}

install_pkg() {
    local pkg_mgr=$(get_package_manager)
    if [ "$pkg_mgr" = "unsupported" ]; then
        echo "Error: Unsupported package manager."
        return 1
    fi

    for pkg in "$@"; do
        case "$pkg_mgr" in
            apt)
                if ! dpkg -s "$pkg" > /dev/null 2>&1; then
                    sudo apt update
                    sudo apt install -y "$pkg"
                fi
                ;;
            dnf|yum)
                if ! rpm -q "$pkg" > /dev/null 2>&1; then
                    sudo "$pkg_mgr" install -y "$pkg"
                fi
                ;;
            pacman)
                if ! pacman -Qi "$pkg" > /dev/null 2>&1; then
                    sudo pacman -Sy --noconfirm "$pkg"
                fi
                ;;
            zypper)
                if ! rpm -q "$pkg" > /dev/null 2>&1; then
                    sudo zypper install -y "$pkg"
                fi
                ;;
        esac
    done
}

install_command git g++ make cmake curl tar

cd "$EXLIBS_DIR"

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

if [ ! -d "rapidjson-1.1.0" ]; then
    curl -fsSL "https://github.com/Tencent/rapidjson/archive/refs/tags/v1.1.0.tar.gz" | tar -xz
fi

if [ ! -d "glew-2.2.0" ]; then
    install_pkg libgl1-mesa-dev libglu1-mesa-dev
    curl -fsSL "https://github.com/nigels-com/glew/releases/download/glew-2.2.0/glew-2.2.0.tgz" | tar -xz
    cd "$EXLIBS_DIR"/glew-2.2.0/build
    cmake ./cmake
    make -j4
    cd "$EXLIBS_DIR"
fi

if [ ! -d "Simple-OpenGL-Image-Library" ]; then
    git clone https://github.com/kbranigan/Simple-OpenGL-Image-Library.git
    cd "$EXLIBS_DIR"/Simple-OpenGL-Image-Library
    make
    cd "$EXLIBS_DIR"
fi
