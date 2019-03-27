//
//  Camera.hpp
//  LearnOpenGL
//
//  Created by hsbcnet.mobile.uk hsbcnet.mobile.uk on 2019/3/18.
//  Copyright © 2019年 chensx. All rights reserved.
//

#ifndef Camera_hpp
#define Camera_hpp

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <iostream>
#include <stdio.h>

typedef enum __cameraMovement {
    CameraMovementForward        = 0,   /* 向‘前’移动 */
    CameraMovementBackward       = 1,
    CameraMovementLeft           = 2,
    CameraMovementRight          = 3,
    CameraMovementUp             = 4,
    CameraMovementDown           = 5
} CameraMovement;

const GLfloat kYaw               = -90.0f;  /* 偏航角 */
const GLfloat kPitch             = 0.0f;    /* 俯仰角 */
const GLfloat kSpeed             = 2.5f;    /* 移动速度 */
const GLfloat kSensitivity       = 0.1f;    /* 敏感度 */
const GLfloat kZoom              = 45.0f;   /* 放大 */

class Camera
{
public:
    // Camera Attributes
    glm::vec3 Position;  //摄像机位置向量
    glm::vec3 Front;     //摄像机方向向量
    glm::vec3 Up;        //摄像机‘上’向量
    glm::vec3 Right;     //摄像机‘右’向量
    glm::vec3 WorldUp;   //世界空间‘上’向量
    
    //Euler Angles
    GLfloat Yaw;         //偏航角
    GLfloat Pitch;       //俯仰角
    
    //Camera options
    GLfloat MovementSpeed;
    GLfloat MouseSensitivity;
    GLfloat Zoom;
    
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = kYaw, float pitch = kPitch);
    
    Camera(GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat worldUpX, GLfloat worldUpY, GLfloat worldUpZ, GLfloat yaw, GLfloat pitch);
    
    glm::mat4 viewMatrix();
    
    void processKeyboard(CameraMovement direction, GLfloat deltaTime);
    
    void processMouseMovement(GLfloat offsetX, GLfloat offsetY, GLboolean constrainPitch = GL_TRUE);
    
    void processMouseScroll(GLfloat offsetY);
    
private:
    /**
     更新摄像机有关向量
     */
    void updateCameraVectors();
};

#endif /* Camera_hpp */
