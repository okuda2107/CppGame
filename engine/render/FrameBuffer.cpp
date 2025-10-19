#include "FrameBuffer.h"

// エンジン内で
FrameBuffer::FrameBuffer() {
    glGenFramebuffers(1, &mBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, mBuffer);

    // カラーバッファを追加
    glGenRenderbuffers(1, &mColorBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, mColorBuffer);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
                              GL_RENDERBUFFER, mColorBuffer);

    // 深度バッファを追加
    glGenRenderbuffers(1, &mDepthBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, mDepthBuffer);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,
                              GL_RENDERBUFFER, mDepthBuffer);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        std::cerr << "Error: scene FBO not complete\n";
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

FrameBuffer::~FrameBuffer() {
    glDeleteFramebuffers(1, &mBuffer);
    glDeleteRenderbuffers(1, &mColorBuffer);
    glDeleteRenderbuffers(1, &mDepthBuffer);
}
