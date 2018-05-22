//
//  ShaderView.m
//  OpenGL
//
//  Created by 陈思欣 on 2018/5/22.
//  Copyright © 2018年 chensx. All rights reserved.
//

#import "ShaderView.h"
#import <OpenGLES/ES2/gl.h> //- - 连引入文件都比一般库NB

@interface ShaderView()

@property (nonatomic, strong) EAGLContext *myContext;
@property (nonatomic, strong) CAEAGLLayer *myEALayer;
@property (nonatomic, assign) GLuint myProgram;


@end

@implementation ShaderView

/*
// Only override drawRect: if you perform custom drawing.
// An empty implementation adversely affects performance during animation.
- (void)drawRect:(CGRect)rect {
    // Drawing code
}
*/

@end
