#pragma once
#include <AL/al.h>

#include <string>

const char* alGetErrorString(ALenum error) {
    switch (error) {
        case AL_NO_ERROR:
            return "AL_NO_ERROR: No error";
        case AL_INVALID_NAME:
            return "AL_INVALID_NAME: Invalid name parameter";
        case AL_INVALID_ENUM:
            return "AL_INVALID_ENUM: Invalid enum parameter value";
        case AL_INVALID_VALUE:
            return "AL_INVALID_VALUE: Invalid parameter value";
        case AL_INVALID_OPERATION:
            return "AL_INVALID_OPERATION: Invalid operation";
        case AL_OUT_OF_MEMORY:
            return "AL_OUT_OF_MEMORY: Unable to allocate memory";
        default:
            return "Unknown AL error";
    }
}
