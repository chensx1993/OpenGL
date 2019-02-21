//
//  SXTriangleViewController.m
//  OpenGLGuide
//
//  Created by 陈思欣 on 2019/2/15.
//  Copyright © 2019 chensx. All rights reserved.
//

#import "SXTriangleViewController.h"
#import "esUtil.h"

extern void esMain( ESContext *esContext );

@interface SXTriangleViewController ()
{
    ESContext _esContext;
}
@property (nonatomic, strong) EAGLContext *context;
@property (nonatomic, strong) GLKBaseEffect *effect;

@end

@implementation SXTriangleViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    self.context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES3];
    if (!self.context) {
        NSLog(@"Failed to create ES context");
    }
    
    GLKView *view = (GLKView *)self.view;
    view.context = self.context;
    view.drawableDepthFormat = GLKViewDrawableDepthFormat24;
    
    [self setupGL];
}

- (void)dealloc {
    [self tearDownGL];
    
    if ([EAGLContext currentContext] == self.context) {
        [EAGLContext setCurrentContext:nil];
    }
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    
    if ([self isViewLoaded] && ([[self view] window] == nil)) {
        self.view = nil;
        
        [self tearDownGL];
        
        if ([EAGLContext currentContext] == self.context) {
            [EAGLContext setCurrentContext:nil];
        }
        self.context = nil;
    }
    
    // Dispose of any resources that can be recreated.
}

- (void)setupGL {
    EAGLContext.currentContext = self.context;
    
    memset(&_esContext, 0, sizeof(_esContext));
    
    esMain(&_esContext);
}

- (void)tearDownGL
{
    EAGLContext.currentContext = self.context;
    if (_esContext.shutdownFunc) {
        _esContext.shutdownFunc( &_esContext);
    }
}

- (void)update {
    if (_esContext.updateFunc) {
        _esContext.updateFunc(&_esContext, self.timeSinceLastUpdate);
    }
}

- (void)glkView:(GLKView *)view drawInRect:(CGRect)rect {
    _esContext.width = view.drawableWidth;
    _esContext.height = view.drawableHeight;
    
    if (_esContext.drawFunc) {
        _esContext.drawFunc( &_esContext);
    }
}


@end
