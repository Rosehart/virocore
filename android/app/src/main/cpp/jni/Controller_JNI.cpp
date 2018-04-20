//
//  Controller_JNI.cpp
//  ViroRenderer
//
//  Copyright © 2016 Viro Media. All rights reserved.
//

#include <jni.h>
#include <memory>
#include <VROInputPresenterDaydream.h>
#include "ViroContext_JNI.h"
#include "EventDelegate_JNI.h"
#include "ARUtils_JNI.h"

#if VRO_PLATFORM_ANDROID
#define VRO_METHOD(return_type, method_name) \
  JNIEXPORT return_type JNICALL              \
      Java_com_viro_core_Controller_##method_name
#endif

extern "C" {

VRO_METHOD(void, nativeSetEventDelegate)(VRO_ARGS
                                         jlong render_context_ref,
                                         jlong native_delegate_ref) {
    std::weak_ptr<ViroContext> nativeContext_w = ViroContext::native(render_context_ref);
    std::weak_ptr<EventDelegate_JNI> delegate_w = EventDelegate::native(native_delegate_ref);

    VROPlatformDispatchAsyncRenderer([nativeContext_w, delegate_w] {
        std::shared_ptr<ViroContext> nativeContext = nativeContext_w.lock();
        std::shared_ptr<EventDelegate_JNI> delegate = delegate_w.lock();

        if (nativeContext && delegate) {
            std::shared_ptr<VROInputPresenter> controllerPresenter
                    = nativeContext->getInputController()->getPresenter();
            controllerPresenter->setEventDelegate(delegate);
        }
    });
}

VRO_METHOD(void, nativeEnableReticle)(VRO_ARGS
                                      jlong render_context_ref,
                                      jboolean enable) {
    std::weak_ptr<ViroContext> nativeContext_w = ViroContext::native(render_context_ref);

    VROPlatformDispatchAsyncRenderer([nativeContext_w, enable] {
        std::shared_ptr<ViroContext> nativeContext = nativeContext_w.lock();
        if (!nativeContext) {
            return;
        }

        std::shared_ptr<VROInputPresenter> controllerPresenter = nativeContext->getInputController()->getPresenter();
        std::shared_ptr<VROReticle> reticle = controllerPresenter->getReticle();
        if (reticle != nullptr) {
            reticle->setEnabled(enable);
        }
    });
}

VRO_METHOD(void, nativeEnableController)(VRO_ARGS
                                         jlong render_context_ref,
                                         jboolean enable) {
    std::weak_ptr<ViroContext> nativeContext_w = ViroContext::native(render_context_ref);

    VROPlatformDispatchAsyncRenderer([nativeContext_w, enable] {
        std::shared_ptr<ViroContext> nativeContext = nativeContext_w.lock();
        if (!nativeContext) {
            return;
        }

        std::shared_ptr<VROInputPresenter> controllerPresenter = nativeContext->getInputController()->getPresenter();
        controllerPresenter->getRootNode()->setHidden(!enable);
    });
}

VRO_METHOD(jfloatArray, nativeGetControllerForwardVector)(VRO_ARGS
                                                          jlong context_j) {
    std::shared_ptr<ViroContext> context = ViroContext::native(context_j);
    VROVector3f position = context->getInputController()->getPresenter()->getLastKnownForward();
    return ARUtilsCreateFloatArrayFromVector3f(position);
}

VRO_METHOD(void, nativeGetControllerForwardVectorAsync)(VRO_ARGS
                                                        jlong native_render_context_ref,
                                                        jobject callback) {
    jweak weakCallback = env->NewWeakGlobalRef(callback);
    std::weak_ptr<ViroContext> helperContext_w = ViroContext::native(native_render_context_ref);

    VROPlatformDispatchAsyncApplication([helperContext_w, weakCallback] {
        JNIEnv *env = VROPlatformGetJNIEnv();
        jobject jCallback = env->NewLocalRef(weakCallback);
        if (jCallback == NULL) {
            return;
        }
        std::shared_ptr<ViroContext> helperContext = helperContext_w.lock();
        if (!helperContext) {
            return;
        }
        VROVector3f position = helperContext->getInputController()->getPresenter()->getLastKnownForward();
        VROPlatformCallJavaFunction(jCallback,
                                    "onGetForwardVector", "(FFF)V", position.x, position.y, position.z);
        env->DeleteLocalRef(jCallback);
        env->DeleteWeakGlobalRef(weakCallback);
    });
}
/**
 * TODO VIRO-704: Add APIs for custom controls - replacing Obj or adding tooltip support.
 */

}  // extern "C"
