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
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


typedef struct
{
    // Handle to a program object
    Shader shader;
    GLuint texture;
    GLuint texture1;
    GLuint VAO;
    GLuint VBO;
    GLuint EBO;
    
} UserData;

int init(ESContext *esContext)
{
    const char *vFileName = GetBundleFileName("5.1.transform.vs");
    const char *fFileName = GetBundleFileName("5.1.transform.fs");
    Shader ourShader(vFileName, fFileName);

    UserData *userData = (UserData *)esContext->userData;
    userData->shader = ourShader;

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[] = {
        // positions         // texture coords
         0.5f,  0.5f, 0.0f,   1.0f, 1.0f, // top right
         0.5f, -0.5f, 0.0f,   1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, // bottom left
        -0.5f,  0.5f, 0.0f,   0.0f, 1.0f  // top left
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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // load and crxeate a texture
    // -------------------------
    unsigned int texture1, texture2;
    
    // texture 1
    // ---------
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    stbi_set_flip_vertically_on_load(true);

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
    
    // texture 2
    // ---------
    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    
    data = stbi_load(GetBundleFileName("timg.jpeg"), &width, &height, &nrChannels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        
    }else {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
    
    ourShader.use();
    ourShader.setUniformInt("texture1", 0);
    ourShader.setUniformInt("texture2", 1);
    
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    userData->texture = texture1;
    userData->texture1 = texture2;
    userData->VAO = VAO;
    userData->VBO = VBO;
    userData->EBO = EBO;

    return TRUE;
}

void draw(ESContext *esContext)
{

    UserData *userData = (UserData *)esContext->userData;
    Shader ourShader = userData->shader;

    glViewport ( 0, 0, esContext->width, esContext->height );
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, userData->texture);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, userData->texture1);
    
    glm::mat4 transform = glm::mat4(1.0f);
    transform = glm::translate(transform, glm::vec3(0.5f, -0.5f, 0.0f));
    transform = glm::rotate(transform, (float)(time(NULL) % 100000), glm::vec3(0.0f, 0.0f, 1.0f));

    ourShader.use();
    ourShader.setUniformMat4("transform", glm::value_ptr(transform));
    
    glBindVertexArray(userData->VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

}

void Shutdown(ESContext *esContext)
{
    UserData *userData = (UserData *)esContext->userData;
    Shader ourShader = userData->shader;
    ourShader.deleteProgram();

    glDeleteVertexArrays(1, &(userData->VAO));
    glDeleteBuffers(1, &(userData->VBO));
    glDeleteBuffers(1, &(userData->EBO));
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
