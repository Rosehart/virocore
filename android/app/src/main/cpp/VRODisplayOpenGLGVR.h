//
// Created by Raj Advani on 8/23/17.
//

#ifndef ANDROID_VRODISPLAYOPENGLGVR_H
#define ANDROID_VRODISPLAYOPENGLGVR_H

#include <memory>
#include "VROOpenGL.h"
#include "VRODisplayOpenGL.h"
#include "vr/gvr/capi/include/gvr.h"
#include "vr/gvr/capi/include/gvr_types.h"

class VRODriverOpenGL;

/*
 In GVR the VRODisplay (the primary framebuffer) is managed by a
 gvr::Frame object.
 */
class VRODisplayOpenGLGVR : public VRODisplayOpenGL {
public:

    VRODisplayOpenGLGVR(std::shared_ptr<VRODriverOpenGL> driver) :
        VRODisplayOpenGL(0, driver),
        _frame(nullptr) {}
    virtual ~VRODisplayOpenGLGVR() {}

    void bind() {
        if (_frame != nullptr) {
            // Unbind first, ensures the previous framebuffer is invalidated (preventing
            // logical buffer stores). Also prevents GVR log spam.
            gvr_frame_unbind(_frame);
            gvr_frame_bind_buffer(_frame, 0);

            glViewport(_viewport.getX(), _viewport.getY(), _viewport.getWidth(), _viewport.getHeight());
            glScissor(_viewport.getX(), _viewport.getY(), _viewport.getWidth(), _viewport.getHeight());
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
        }
        else {
            // 360 mode, we don't use the gvr frame but we have a valid framebuffer object
            VRODisplayOpenGL::bind();
        }
    }

    void setFrame(gvr::Frame &frame) {
        _frame = frame.cobj();
    }

    void clearFrame() {
        _frame = nullptr;
    }

private:
    gvr_frame *_frame;

};


#endif //ANDROID_VRODISPLAYOPENGLGVR_H