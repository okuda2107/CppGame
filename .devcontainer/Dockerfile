FROM mcr.microsoft.com/vscode/devcontainers/base:ubuntu-20.04

RUN apt-get update \
    && apt-get install -y \
        build-essential

RUN apt-get update \
    && apt-get install -y \
        libgl1-mesa-dev xorg-dev

ENV PATH $PATH:/workspaces/cppGame/External/SDL/include/SDL \
    :/workspaces/cppGame/External/SOIL/include/SOIL \
    :/workspaces/cppGame/External/GLEW/include/GL \
    :/workspaces/cppGame/External/rapidjson/include/rapidjson

ENV DISPLAY host.docker.internal:0.0
