FROM ubuntu:22.04

# create user
ARG USER=vscode
ARG GID=1000
ARG UID=1000
RUN apt-get update \
    && apt-get install -y sudo \
    && echo "$USER ALL=(ALL) NOPASSWD:ALL" >>/etc/sudoers.d/ALL \
    && groupadd \
        --gid $GID \
        $USER \
    && useradd \
        --uid $UID \
        --gid $GID \
        --home-dir /home/$USER \
        --create-home \
        --shell /bin/bash \
        $USER

RUN apt-get update \
    && apt-get install -y g++ make

RUN apt-get update \
    && apt-get install -y libsdl2-dev libsdl2-image-dev libsdl2-mixer-dev libsdl2-net-dev libsdl2-ttf-dev

RUN apt-get update \
    && apt-get install -y libsoil-dev

RUN apt-get update \
    && apt-get install -y libglew-dev

RUN apt-get update \
    && apt-get install -y rapidjson-dev

ENV CPLUS_INCLUDE_PATH /usr/include/SDL2:/usr/include/SOIL:/usr/include/GL:/usr/include/rapidjson:/workspace/inc

USER $USER

RUN sudo apt update && sudo apt install -y \
    x11-apps \
  && sudo apt clean \
  && sudo rm -rf /var/lib/apt/lists/*
