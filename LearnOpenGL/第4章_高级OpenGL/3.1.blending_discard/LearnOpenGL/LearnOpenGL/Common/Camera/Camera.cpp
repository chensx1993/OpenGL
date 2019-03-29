//
//  Camera.cpp
//  LearnOpenGL
//
//  Created by hsbcnet.mobile.uk hsbcnet.mobile.uk on 2019/3/18.
//  Copyright © 2019年 chensx. All rights reserved.
//

#include "Camera.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(kSpeed), MouseSensitivity(kSensitivity), Zoom(kZoom)
{
    Position = position;
    WorldUp = up;
    Yaw = yaw;
    Pitch = pitch;
    updateCameraVectors();
}

Camera::Camera(GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat worldUpX, GLfloat worldUpY, GLfloat worldUpZ, GLfloat yaw, GLfloat pitch) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(kSpeed), MouseSensitivity(kSensitivity), Zoom(kZoom)
{
    Position = glm::vec3(posX, posY, posZ);
    WorldUp = glm::vec3(worldUpX, worldUpY, worldUpZ);
    Yaw = yaw;
    Pitch = pitch;
    updateCameraVectors();
}

glm::mat4 Camera::viewMatrix()
{
    return glm::lookAt(Position, Position + Front, Up);
}

void Camera::processKeyboard(CameraMovement direction, GLfloat deltaTime)
{
    GLfloat velocity = MovementSpeed * deltaTime;
    if (direction == CameraMovementForward) {
        Position += Front * velocity;
        
    }else if (direction == CameraMovementBackward) {
        Position -= Front * velocity;
        
    }else if (direction == CameraMovementLeft) {
        Position -= Right * velocity;
        
    }else if (direction == CameraMovementRight) {
        Position += Right * velocity;
        
    }else if (direction == CameraMovementUp) {
        Position += Up * velocity;
        
    }else if (direction == CameraMovementDown) {
        Position -= Up * velocity;
    }
}

void Camera::processMouseMovement(GLfloat offsetX, GLfloat offsetY, GLboolean constrainPitch)
{
    offsetX *= MouseSensitivity;
    offsetY *= MouseSensitivity;
    
#ifdef __APPLE__
    Yaw -= offsetX;
    Pitch -= offsetY;
#else
    Yaw   += offsetX;
    Pitch += offsetY;
#endif
    
    // Make sure that when pitch is out of bounds, screen doesn't get flipped
    if (constrainPitch)
    {
        if (Pitch > 89.0f)
        Pitch = 89.0f;
        if (Pitch < -89.0f)
        Pitch = -89.0f;
    }
    // Update Front, Right and Up Vectors using the updated Euler angles
    updateCameraVectors();
}

void Camera::processMouseScroll(GLfloat offsetY)
{
    if (Zoom >= 1.0f && Zoom <= 45.0f) {
        Zoom -= offsetY;
        
    }else if (Zoom <= 1.0f) {
        Zoom = 1.0f;
        
    }else if (Zoom >= 45.0f) {
        Zoom = 45.0f;
    }
}

void Camera::updateCameraVectors()
{
    // Calculate the new Front vector
    glm::vec3 front;
    front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    front.y = sin(glm::radians(Pitch));
    front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    
    Front = glm::normalize(front);
    // Also re-calculate the Right and Up vector
    Right = glm::normalize(glm::cross(Front, WorldUp));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
    Up    = glm::normalize(glm::cross(Right, Front));
}
                                                                                                                                                             
                                                                                                                                                             
