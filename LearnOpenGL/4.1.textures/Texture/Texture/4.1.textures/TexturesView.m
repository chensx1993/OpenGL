//
//  TexturesView.m
//  Texture
//
//  Created by 陈思欣 on 2019/2/28.
//  Copyright © 2019 chensx. All rights reserved.
//

#import "TexturesView.h"
#include "esUtil.h"

@interface TexturesView()<GLKViewDelegate>

@property (nonatomic, strong) EAGLContext *mContext;
@property (nonatomic, strong) GLKBaseEffect *mEffect;

@property (nonatomic, assign) ESContext esContext;

@end

@implementation TexturesView

- (instancetype)initWithFrame:(CGRect)frame {
    if (self = [super initWithFrame:frame]) {
        
    }
    return self;
}

- (void)awakeFromNib {
    [super awakeFromNib];
}

- (void)setup {
     [self setupConfig];
}

- (void)setupConfig {
    //kEAGLRenderingAPIOpenGLES2 OpenGL ES版本: 2.0  还有1.0 3.0
    self.mContext = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES3];
    
    GLKView *view = (GLKView *)self;
    view.context = self.mContext;
    view.delegate = self;
    
    //颜色缓冲区
    view.drawableColorFormat = GLKViewDrawableColorFormatRGBA8888;
    [EAGLContext setCurrentContext:self.mContext];
}



#pragma mark - GLKViewDelegate

- (void)update {
    
}

- (void)glkView:(GLKView *)view drawInRect:(CGRect)rect {
    
}

@end
