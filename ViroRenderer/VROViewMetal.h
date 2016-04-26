//
//  VROViewMetal.h
//  ViroRenderer
//
//  Created by Raj Advani on 4/22/16.
//  Copyright © 2016 Viro Media. All rights reserved.
//

#import <Metal/Metal.h>
#import <MetalKit/MetalKit.h>
#import <memory>

class VRODriverMetal;

@interface VROViewMetal : MTKView <MTKViewDelegate>

- (id)initWithFrame:(CGRect)frame device:(id <MTLDevice>)device
             driver:(std::shared_ptr<VRODriverMetal>)driver;

@end
