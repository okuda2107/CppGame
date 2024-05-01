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
    && apt-get install -y --no-install-recommends \
        g++ make \
        libsdl2-dev libsdl2-image-dev libsdl2-mixer-dev libsdl2-net-dev libsdl2-ttf-dev \
        libsoil-dev \
        libglew-dev libgl1-mesa-dev xorg-dev \
        libopenal-dev \
        rapidjson-dev \
        gcc-mingw-w64 g++-mingw-w64 \
        python3 pip \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*

USER $USER
