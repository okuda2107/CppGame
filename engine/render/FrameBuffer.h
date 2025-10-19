#pragma once
#include "glew.h"

class FrameBuffer {
    unsigned int mBuffer;
    unsigned int mColorBuffer;
    unsigned int mDepthBuffer;

   public:
    FrameBuffer();
    ~FrameBuffer();
}
