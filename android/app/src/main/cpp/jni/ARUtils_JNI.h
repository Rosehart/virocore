//
//  ARUtils_JNI.h
//  ViroRenderer
//
//  Copyright © 2017 Viro Media. All rights reserved.
//

#ifndef ANDROID_ARUTILS_JNI_H
#define ANDROID_ARUTILS_JNI_H


#include <jni.h>
#include <VROARPlaneAnchor.h>
#include <VROARHitTestResult.h>

// Helper functions to create a Java ARAnchor object
jobject ARUtilsCreateJavaARAnchorFromAnchor(std::shared_ptr<VROARAnchor> anchor);
jfloatArray ARUtilsCreateFloatArrayFromVector3f(VROVector3f vector);
jfloatArray ARUtilsCreateFloatArrayFromMatrix(VROMatrix4f matrix);
jstring ARUtilsCreateStringFromAlignment(VROARPlaneAlignment alignment);
jobject ARUtilsCreateARHitTestResult(VROARHitTestResult result);


// Helper functions to create a Java ARPointCloud object
jobject ARUtilsCreateARPointCloud(std::shared_ptr<VROARPointCloud> pointCloud);


#endif //ANDROID_ARUTILS_JNI_H