//
//  VRORenderLoopCardboard.h
//  ViroRenderer
//
//  Created by Raj Advani on 4/22/16.
//  Copyright © 2016 Viro Media. All rights reserved.
//

#import <UIKit/UIKit.h>

@class VROViewCardboard;

@interface VRORenderLoopCardboard : NSObject

/*
 Initializes the render loop with target and selector. The underlying |CADisplayLink| instance
 holds a strong reference to the target until the |invalidate| method is called.
 */
- (instancetype)initWithRenderTarget:(id)target selector:(SEL)selector;

/*
 Invalidates this instance and the underlying |CADisplayLink| instance releases its strong
 reference to the render target.
 */
- (void)invalidate;

/*
 Sets or returns the paused state of the underlying |CADisplayLink| reference. 
 */
@property(nonatomic) BOOL paused;

@end

/*
 Interface used to maintain a weak reference from the render loop to the
 cardboard view.
 */
@interface VRORenderLoopTarget : NSObject

@property (readwrite, nonatomic) VROViewCardboard *cardboardView;

- (void)render;

@end
