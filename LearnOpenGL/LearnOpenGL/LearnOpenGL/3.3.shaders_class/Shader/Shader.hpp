//
//  Shader.hpp
//  LearnOpenGL
//
//  Created by 陈思欣 on 2019/2/27.
//  Copyright © 2019 chensx. All rights reserved.
//

#ifndef Shader_hpp
#define Shader_hpp

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdio.h>

class Shader
{
public:
    unsigned int ID;
    
    Shader(const char* vertexPath, const char* fragmentPath);
    
    void use();
    
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;
    
private:
    void checkCompileErrors(unsigned int shader, std::string type);
    
};

#endif /* Shader_hpp */
