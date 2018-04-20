//
//  Image_JNI.cpp
//  ViroRenderer
//
//  Copyright © 2016 Viro Media. All rights reserved.
//
#include <jni.h>
#include <memory>
#include <VROPlatformUtil.h>

#include "Image_JNI.h"
#include "Texture_JNI.h"

#if VRO_PLATFORM_ANDROID
#define VRO_METHOD(return_type, method_name) \
  JNIEXPORT return_type JNICALL              \
      Java_com_viro_core_internal_Image_##method_name
#endif

extern "C" {

VRO_METHOD(jlong, nativeCreateImage)(VRO_ARGS
                                     jstring resource, jstring format) {
    std::string strResource = VROPlatformGetString(resource, env);

    VROTextureInternalFormat internalFormat = Texture::getFormat(env, format);
    std::shared_ptr<VROImageAndroid> imagePtr = std::make_shared<VROImageAndroid>(strResource, internalFormat);

    return Image::jptr(imagePtr);
}

VRO_METHOD(jlong, nativeCreateImageFromBitmap)(VRO_ARGS
                                               jobject jbitmap, jstring format) {
    VROPlatformSetEnv(env);
    VROTextureInternalFormat internalFormat = Texture::getFormat(env, format);
    std::shared_ptr<VROImageAndroid> imagePtr = std::make_shared<VROImageAndroid>(jbitmap, internalFormat);
    return Image::jptr(imagePtr);
}

VRO_METHOD(jlong, nativeGetWidth)(VRO_ARGS
                                  jlong nativeRef) {
    return Image::native(nativeRef).get()->getWidth();
}

VRO_METHOD(jlong, nativeGetHeight)(VRO_ARGS
                                   jlong nativeRef) {
    return Image::native(nativeRef).get()->getHeight();
}

VRO_METHOD(void, nativeDestroyImage)(VRO_ARGS
                                     jlong nativeRef) {
    delete reinterpret_cast<PersistentRef<VROImageAndroid> *>(nativeRef);
}

} // extern "C"