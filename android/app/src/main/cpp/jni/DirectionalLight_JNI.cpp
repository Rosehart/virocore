//
// DirectionalLight_JNI.cpp
// ViroRenderer
//
// Copyright © 2016 Viro Media. All rights reserved.

#include <jni.h>
#include <VROLight.h>
#include <PersistentRef.h>
#include <VRONode.h>
#include <VROPlatformUtil.h>
#include "Node_JNI.h"

#if VRO_PLATFORM_ANDROID
#define VRO_METHOD(return_type, method_name) \
  JNIEXPORT return_type JNICALL              \
      Java_com_viro_core_DirectionalLight_##method_name
#endif

namespace DirectionalLight {
    inline VRO_REF jptr(std::shared_ptr<VROLight> shared_node) {
        PersistentRef<VROLight> *native_light = new PersistentRef<VROLight>(shared_node);
        return reinterpret_cast<intptr_t>(native_light);
    }

    inline std::shared_ptr<VROLight> native(VRO_REF ptr) {
        PersistentRef<VROLight> *persistentBox = reinterpret_cast<PersistentRef<VROLight> *>(ptr);
        return persistentBox->get();
    }
}

extern "C" {

VRO_METHOD(jlong, nativeCreateDirectionalLight)(VRO_ARGS
                                                jlong color,
                                                jfloat intensity,
                                                jfloat directionX,
                                                jfloat directionY,
                                                jfloat directionZ) {

    std::shared_ptr<VROLight> directionalLight = std::make_shared<VROLight>(VROLightType::Directional);

    // Get the color
    float r = ((color >> 16) & 0xFF) / 255.0;
    float g = ((color >> 8) & 0xFF) / 255.0;
    float b = (color & 0xFF) / 255.0;

    VROVector3f vecColor(r, g, b);
    directionalLight->setColor(vecColor);
    directionalLight->setIntensity(intensity);

    VROVector3f vecDirection(directionX, directionY, directionZ);
    directionalLight->setDirection(vecDirection);

    return DirectionalLight::jptr(directionalLight);
}

// Setters

VRO_METHOD(void, nativeSetDirection)(VRO_ARGS
                                     jlong native_light_ref,
                                     jfloat directionX,
                                     jfloat directionY,
                                     jfloat directionZ) {
    std::weak_ptr<VROLight> light_w = DirectionalLight::native(native_light_ref);

    VROPlatformDispatchAsyncRenderer([light_w, directionX, directionY, directionZ] {
        std::shared_ptr<VROLight> light = light_w.lock();
        if (!light) {
            return;
        }
        VROVector3f vecDirection(directionX, directionY, directionZ);
        light->setDirection(vecDirection);
    });
}


VRO_METHOD(void, nativeSetCastsShadow)(VRO_ARGS
                                       jlong native_light_ref,
                                       jboolean castsShadow) {
    std::weak_ptr<VROLight> light_w = DirectionalLight::native(native_light_ref);
    VROPlatformDispatchAsyncRenderer([light_w, castsShadow] {
        std::shared_ptr<VROLight> light = light_w.lock();
        if (!light) {
            return;
        }
        light->setCastsShadow(castsShadow);
    });
}

VRO_METHOD(void, nativeSetShadowOrthographicSize)(VRO_ARGS
                                                  jlong native_light_ref,
                                                  jfloat size) {

    std::weak_ptr<VROLight> light_w = DirectionalLight::native(native_light_ref);
    VROPlatformDispatchAsyncRenderer([light_w, size] {
        std::shared_ptr<VROLight> light = light_w.lock();
        if(!light) {
            return;
        }
        light->setShadowOrthographicSize(size);
    });
}

VRO_METHOD(void, nativeSetShadowOrthographicPosition)(VRO_ARGS
                                                      jlong native_light_ref,
                                                      jfloat posX,
                                                      jfloat posY,
                                                      jfloat posZ) {

    std::weak_ptr<VROLight> light_w = DirectionalLight::native(native_light_ref);
    VROPlatformDispatchAsyncRenderer([light_w, posX, posY, posZ] {
        std::shared_ptr<VROLight> light = light_w.lock();
        if(!light) {
            return;
        }
        VROVector3f vecPosition(posX, posY, posZ);
        light->setPosition(vecPosition);
    });
}

VRO_METHOD(void, nativeSetShadowMapSize)(VRO_ARGS
                                         jlong native_light_ref,
                                         jint size) {

    std::weak_ptr<VROLight> light_w = DirectionalLight::native(native_light_ref);

    VROPlatformDispatchAsyncRenderer([light_w, size] {
        std::shared_ptr<VROLight> light = light_w.lock();
        if(!light) {
            return;
        }
        light->setShadowMapSize(size);
    });
}

VRO_METHOD(void, nativeSetShadowOpacity)(VRO_ARGS
                                         jlong native_light_ref,
                                         float opacity) {

    std::weak_ptr<VROLight> light_w = DirectionalLight::native(native_light_ref);

    VROPlatformDispatchAsyncRenderer([light_w, opacity] {
        std::shared_ptr<VROLight> light = light_w.lock();
        if(!light) {
            return;
        }
        light->setShadowOpacity(opacity);
    });
}

VRO_METHOD(void, nativeSetShadowBias)(VRO_ARGS
                                      jlong native_light_ref,
                                      jfloat bias) {

    std::weak_ptr<VROLight> light_w = DirectionalLight::native(native_light_ref);

    VROPlatformDispatchAsyncRenderer([light_w, bias] {
        std::shared_ptr<VROLight> light = light_w.lock();
        if(!light) {
            return;
        }
        light->setShadowBias(bias);
    });
}


VRO_METHOD(void, nativeSetShadowNearZ)(VRO_ARGS
                                       jlong native_light_ref,
                                       jfloat shadowNearZ) {

    std::weak_ptr<VROLight> light_w = DirectionalLight::native(native_light_ref);

    VROPlatformDispatchAsyncRenderer([light_w, shadowNearZ] {
        std::shared_ptr<VROLight> light = light_w.lock();
        if(!light) {
            return;
        }
        light->setShadowNearZ(shadowNearZ);
    });
}

VRO_METHOD(void, nativeSetShadowFarZ)(VRO_ARGS
                                      jlong native_light_ref,
                                      jfloat shadowFarZ) {


    std::weak_ptr<VROLight> light_w = DirectionalLight::native(native_light_ref);
    VROPlatformDispatchAsyncRenderer([light_w, shadowFarZ] {
        std::shared_ptr<VROLight> light = light_w.lock();
        if(!light) {
            return;
        }
        light->setShadowFarZ(shadowFarZ);
    });
}

} // extern "C"