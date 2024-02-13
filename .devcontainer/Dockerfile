FROM mcr.microsoft.com/vscode/devcontainers/base:ubuntu-20.04

RUN apt-get update \
    && apt-get install -y build-essential

RUN apt-get update \
    && apt-get install -y libgl1-mesa-dev xorg-dev

RUN apt-get update \
    && apt-get install -y libsdl2-dev libsdl2-image-dev libsdl2-mixer-dev libsdl2-net-dev libsdl2-ttf-dev

RUN apt-get update \
    && apt-get install -y libsoil-dev

RUN apt-get update \
    && apt-get install -y libglew-dev

RUN apt-get update \
    && apt-get install -y rapidjson-dev

ENV CPLUS_INCLUDE_PATH /usr/include/SDL2:/usr/include/SOIL:/usr/include/GL:/usr/include/rapidjson:/workspaces/CppGame/inc

ENV DISPLAY host.docker.internal:0.0
