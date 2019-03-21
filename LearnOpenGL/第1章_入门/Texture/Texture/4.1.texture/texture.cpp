//
//  texture.cpp
//  Texture
//
//  Created by hsbcnet.mobile.uk hsbcnet.mobile.uk on 2019/3/8.
//  Copyright © 2019年 chensx. All rights reserved.
//

//#include "esUtil.h"
#include "Shader.hpp"
#include "FileWrapper.hpp"
#include "stb_image.h"


typedef struct
{
    // Handle to a program object
    Shader shader;
    GLuint texture;
    GLuint VAO;
    
} UserData;

int init(ESContext *esContext)
{
    const char *vFileName = GetBundleFileName("4.1.texture.vs");
    const char *fFileName = GetBundleFileName("4.1.texture.fs");
    Shader ourShader(vFileName, fFileName);

    UserData *userData = (UserData *)esContext->userData;
    userData->shader = ourShader;

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[] = {
        // positions          // colors           // texture coords
        0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
        0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left
    };
    unsigned int indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };

    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    // load and crxeate a texture
    // -------------------------
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nrChannels;
    unsigned char *data = stbi_load(GetBundleFileName("container.jpg"), &width, &height, &nrChannels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
     glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    userData->texture = texture;
    userData->VAO = VAO;

    return TRUE;
}

void draw(ESContext *esContext)
{

    UserData *userData = (UserData *)esContext->userData;
    Shader ourShader = userData->shader;

    glViewport ( 0, 0, esContext->width, esContext->height );
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glBindTexture(GL_TEXTURE_2D, userData->texture);

    ourShader.use();
    glBindVertexArray(userData->VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

}

void Shutdown(ESContext *esContext)
{
    UserData *userData = (UserData *)esContext->userData;
    Shader ourShader = userData->shader;
    ourShader.deleteProgram();

}

int textureMain(ESContext *esContext)
{
    esContext->userData = malloc ( sizeof ( UserData ) );
    if (!init(esContext)) {
        return GL_FALSE;
    }
    
    esRegisterShutdownFunc ( esContext, Shutdown );
    esRegisterDrawFunc ( esContext, draw );
    
    return GL_TRUE;
}
