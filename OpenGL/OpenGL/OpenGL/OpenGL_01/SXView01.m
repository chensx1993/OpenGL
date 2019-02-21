//
//  SXView01.m
//  OpenGL
//
//  Created by 陈思欣 on 2018/5/22.
//  Copyright © 2018年 chensx. All rights reserved.
//

#import "SXView01.h"
#import <GLKit/GLKit.h>

#define kEBO 1

@interface SXView01()<GLKViewDelegate>

@property (nonatomic, strong) EAGLContext *mContext;
@property (nonatomic, strong) GLKBaseEffect *mEffect;

@end

@implementation SXView01

- (instancetype)initWithFrame:(CGRect)frame {
    if (self = [super initWithFrame:frame]) {
        [self setup];
    }
    return self;
}

- (void)awakeFromNib {
    [super awakeFromNib];
    [self setup];
}

- (void)setup {
    [self setupConfig];
    [self uploadVertexArray];
    [self setupVertexAttribPointer];
    [self uploadTexture];
}


- (void)setupConfig {
    //kEAGLRenderingAPIOpenGLES2 OpenGL ES版本: 2.0  还有1.0 3.0
    self.mContext = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2];
    
    GLKView *view = (GLKView *)self;
    view.context = self.mContext;
    view.delegate = self;
    
    //颜色缓冲区
    view.drawableColorFormat = GLKViewDrawableColorFormatRGBA8888;
    [EAGLContext setCurrentContext:self.mContext];
}


#if kEBO == 0
/**  方法介绍
 
 //参数一: 缓冲类型
 //参数二：指定传输对象的大小
 //参数三：发送的数据
 //参数四: 显卡如何管理数据
 //GL_STREAM_DRAW  数据不会或几乎不会改变
 //GL_STATIC_DRAW  数据会变改变很多
 //GL_DYNAMIC_DRAW 数据每次绘制时都会改变
 
 //把顶点数据复制到缓冲的内存中(cpu内存 -> gpu内存)
 glBufferData (GLenum target, GLsizeiptr size, const GLvoid* data, GLenum usage);
 
 
 */
- (void)uploadVertexArray {
    //OpenGL: 任何事物都是在3D空间中
    //不懂为什么需要画两个三角形，直接用4个点画一个正方形不行么？？？
    //->因为：BeginMode(渲染类型): GL_POINTS(点)   GL_TRIANGLES(三角形)  GL_LINE_STRIP(线)
    
    //顶点数据，前三个是顶点坐标，后面两个是纹理坐标
    GLfloat vertexData[] =
    {
        //位置              //纹理
        0.5, -0.5, 0.0f,    1.0f, 0.0f, //右下
        0.5, 0.5, -0.0f,    1.0f, 1.0f, //右上
        -0.5, 0.5, 0.0f,    0.0f, 1.0f, //左上
        
        0.5, -0.5, 0.0f,    1.0f, 0.0f, //右下
        -0.5, 0.5, 0.0f,    0.0f, 1.0f, //左上
        -0.5, -0.5, 0.0f,   0.0f, 0.0f, //左下
    };
    
    GLuint VBO;
    //生成一个VBO对象(顶点缓冲对象) bufferID:会生成一个独一无二的ID
    glGenBuffers(1, &VBO);
    
    //参数一: 缓冲对象类型    参数二: 缓冲ID
    //顶点缓冲对象: GL_ARRAY_BUFFER
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    
    //把顶点数据复制到缓冲的内存中(cpu内存 -> gpu内存)
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
    
}

#else

/*
 思考题：1.代码中有6个顶点坐标，能否使用更少的顶点显示一个图像？
 */
- (void)uploadVertexArray {
    GLfloat vertices[] = {
        0.5, -0.5, 0.0f,    1.0f, 0.0f, //右下
        0.5, 0.5, -0.0f,    1.0f, 1.0f, //右上
        -0.5, 0.5, 0.0f,    0.0f, 1.0f, //左上
        -0.5, -0.5, 0.0f,   0.0f, 0.0f, //左下
    };
    
    GLuint indices[] = {
        0, 1, 2, //第一个三角形
        0, 2, 3  //第二个三角形
    };
    
    
    //1.绑定VBO
    GLuint VBO;
    glGenBuffers(1, &VBO);
    
    // 2. 把我们的顶点数组复制到一个顶点缓冲中，供OpenGL使用
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    // 绑定EBO
    GLuint EBO;
    glGenBuffers(1, &EBO);
    
    // 3. 复制我们的索引数组到一个索引缓冲中，供OpenGL使用
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);//GL_ELEMENT_ARRAY_BUFFER 索引缓冲对象(EBO)
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
}

#endif

/**
 设置顶点属性
 //设置合适的格式从buffer里面读取数据
 //参数一:顶点属性类型
 //参数二:顶点属性大小: 顶点坐标值 为 3
 //参数三:顶点数据类型
 //参数四:步长(stride): 连续的顶点属性组之间的间隔
 //参数五:（void *）位置信息在缓冲中起始位置的偏移量(Offset)
 
 //设置合适的格式从buffer里面读取数据
 glVertexAttribPointer (GLuint indx, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid* ptr)
 
 */
- (void)setupVertexAttribPointer {
    //顶点数据缓冲
    glEnableVertexAttribArray(GLKVertexAttribPosition);//开启对应的顶点属性(默认是禁止的)
    //设置合适的格式从buffer里面读取数据
    glVertexAttribPointer(GLKVertexAttribPosition, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 5, (GLfloat *)NULL + 0);
    
    //纹理
    glEnableVertexAttribArray(GLKVertexAttribTexCoord0);
    glVertexAttribPointer(GLKVertexAttribTexCoord0, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 5, (GLfloat *)NULL + 3);
}


- (void)uploadTexture {
    NSString *filePath = [[NSBundle mainBundle] pathForResource:@"for_test" ofType:@"jpg"];
    //纹理坐标系是相反的
    NSDictionary *options = @{GLKTextureLoaderOriginBottomLeft : @(1)};
    GLKTextureInfo *textureInfo = [GLKTextureLoader textureWithContentsOfFile:filePath options:options error:nil];
    
    //着色器
    self.mEffect = [[GLKBaseEffect alloc] init];
    self.mEffect.texture2d0.enabled = GL_TRUE;
    self.mEffect.texture2d0.name = textureInfo.name;
}

#pragma mark - GLKViewDelegate
- (void)glkView:(GLKView *)view drawInRect:(CGRect)rect {
    glClearColor(0.3f, 0.6f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    //启动着色器
    [self.mEffect prepareToDraw];
    
#if kEBO == 0
    //参数一：渲染类型
    //参数二：起始索引
    //参数三：绘制的点的数量
    glDrawArrays(GL_TRIANGLES, 0, 6);
#else
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
#endif
}

@end
