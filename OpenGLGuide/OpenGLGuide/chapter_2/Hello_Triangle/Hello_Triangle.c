//
//  Hello_Triangle.c
//  OpenGLGuide
//
//  Created by 陈思欣 on 2019/2/18.
//  Copyright © 2019 chensx. All rights reserved.
//

#include "esUtil.h"

typedef struct
{
    GLuint programObject;
} UserData;

GLuint LoadShader (GLenum type, const char *shaderSrc)
{
    GLuint shader;
    GLint compiled;
    
    shader = glCreateShader(type);
    
    if (shader == 0) {
        return 0;
    }
    
    glShaderSource(shader, 1, &shaderSrc, NULL);
    
    glCompileShader(shader);
    
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
    
    if (!compiled) {
        GLint infoLen = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
        
        if (infoLen > 1) {
            char *infoLog = malloc ( sizeof ( char ) * infoLen );
            
            glGetShaderInfoLog(shader, infoLen, NULL, infoLog);
            esLogMessage ( "Error compiling shader:\n%s\n", infoLog );
            
            free(infoLog);
        }
        
        glDeleteShader(shader);
        return 0;
    }
    return shader;
}

int Init (ESContext *esContext)
{
    UserData *userData = esContext->userData;
    char vShaderStr[] =
    "#version 300 es                          \n" //版本 V3.00
    "layout(location = 0) in vec4 vPosition;  \n"
    "void main()                              \n"
    "{                                        \n"
    "   gl_Position = vPosition;              \n"
    "}                                        \n";
    
    char fShaderStr[] =
    "#version 300 es                              \n"
    "precision mediump float;                     \n"
    "out vec4 fragColor;                          \n"
    "void main()                                  \n"
    "{                                            \n"
    "   fragColor = vec4 ( 1.0, 0.0, 0.0, 1.0 );  \n"
    "}                                            \n";
    
    GLuint vertexShader;
    GLuint fragmentShader;
    GLuint programObject;
    GLint linked;
    
    vertexShader = LoadShader(GL_VERTEX_SHADER, vShaderStr);
    fragmentShader = LoadShader(GL_FRAGMENT_SHADER, fShaderStr);
    
    programObject = glCreateProgram();
    if (programObject == 0) {
        return 0;
    }
    
    glAttachShader(programObject, vertexShader);
    glAttachShader(programObject, fragmentShader);
    
    glLinkProgram(programObject);
    
    glGetProgramiv(programObject, GL_LINK_STATUS, &linked);
    
    if (linked  == GL_FALSE )
    {
        GLint infoLen = 0;
        
        glGetProgramiv ( programObject, GL_INFO_LOG_LENGTH, &infoLen );
        
        if ( infoLen > 1 )
        {
            char *infoLog = malloc ( sizeof ( char ) * infoLen );
            
            glGetProgramInfoLog ( programObject, infoLen, NULL, infoLog );
            esLogMessage ( "Error linking program:\n%s\n", infoLog );
            
            free ( infoLog );
        }
        
        glDeleteProgram ( programObject );
        return FALSE;
    }
    
    // Store the program object
    userData->programObject = programObject;
    
    glClearColor ( 1.0f, 1.0f, 1.0f, 0.0f );
    return TRUE;
    
}

///
// Draw a triangle using the shader pair created in Init()
//
void Draw ( ESContext *esContext )
{
    UserData *userData = esContext->userData;
    GLfloat vVertices[] = {  0.0f,  0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f
    };
    
    // Set the viewport
    glViewport ( 0, 0, esContext->width, esContext->height );
    
    // Clear the color buffer
    glClear ( GL_COLOR_BUFFER_BIT );
    
    // Use the program object
    glUseProgram ( userData->programObject );
    
    // Load the vertex data
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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, vVertices );
    glEnableVertexAttribArray ( 0 );
    
    glDrawArrays ( GL_TRIANGLES, 0, 3 );
}

void Shutdown (ESContext *esContext)
{
    UserData *userData = esContext->userData;
    glDeleteProgram(userData->programObject);
}

int esMain(ESContext *esContext)
{
    esContext->userData = malloc(sizeof(UserData));
    esCreateWindow(esContext, "Hello Triangle", 320, 240, ES_WINDOW_RGB);
    
    if (!Init(esContext)) {
        return GL_FALSE;
    }
    
    esRegisterShutdownFunc(esContext, Shutdown);
    esRegisterDrawFunc(esContext, Draw);
    return GL_TRUE;
}
