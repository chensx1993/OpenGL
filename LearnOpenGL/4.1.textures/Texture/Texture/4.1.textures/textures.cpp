//
//  textures.cpp
//  Texture
//
//  Created by 陈思欣 on 2019/2/28.
//  Copyright © 2019 chensx. All rights reserved.
//

#include "esUtil.h"

typedef struct
{
    GLuint programObject;
} UserData;

///
// Create a shader object, load the shader source, and
// compile the shader.
//
GLuint LoadShader ( GLenum type, const char *shaderSrc )
{
    GLuint shader;
    GLint compiled;
    
    // Create the shader object
    shader = glCreateShader ( type );
    
    if ( shader == 0 )
    {
        return 0;
    }
    
    // Load the shader source
    glShaderSource ( shader, 1, &shaderSrc, NULL );
    
    // Compile the shader
    glCompileShader ( shader );
    
    // Check the compile status
    glGetShaderiv ( shader, GL_COMPILE_STATUS, &compiled );
    
    if ( !compiled ) {
        GLint infoLen = 0;
        glGetShaderiv ( shader, GL_INFO_LOG_LENGTH, &infoLen );
        
        if ( infoLen > 1 ) {
            char *infoLog = malloc(sizeof(char) * infoLen);
            
            glGetShaderInfoLog ( shader, infoLen, NULL, infoLog );
            esLogMessage ( "Error compiling shader:\n%s\n", infoLog );
            
            free ( infoLog );
        }
        glDeleteShader ( shader );
        return 0;
    }
    return shader;
}
