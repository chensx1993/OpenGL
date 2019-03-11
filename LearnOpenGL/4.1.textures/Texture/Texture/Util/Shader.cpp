//
//  Shader.cpp
//  
//
//  Created by shenyuanluo on 2017/8/11.
//  Copyright © 2017年 http://blog.shenyuanluo.com/ All rights reserved.
//

#include "Shader.hpp"
#define LOG_BUF_LEN 512     /* log 输出缓冲区长度 */

#pragma mark - Public
#pragma mark -- 构造函数
Shader::Shader(const GLchar* vCodePath, const GLchar* fCodePath)
{
    std::string vString;
    std::string fString;
    std::ifstream vsFile;
    std::ifstream fsFile;
    /* 确保 ifstream 对象可以抛出异常 */
    vsFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fsFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    
    /* 读取 GLSL */
    try
    {
        /* 打开文件 */
        vsFile.open(vCodePath);
        fsFile.open(fCodePath);
        
        std::stringstream vsStream;
        std::stringstream fsStream;
        
        /* 读取文件流 */
        vsStream << vsFile.rdbuf();
        fsStream << fsFile.rdbuf();
        
        /* 关闭文件 */
        vsFile.close();
        fsFile.close();
        
        /* 文件流转换成 String 字符串 */
        vString = vsStream.str();
        fString = fsStream.str();
    }
    catch (std::ifstream::failure e)
    {
        std::cout << "读取 GLSL 文件失败！" << std::endl;
    }
    
    /* String 字符串转换成 const GLchar* */
    const GLchar* vsCode = vString.c_str();
    const GLchar* fsCode = fString.c_str();
    
    GLuint vShaderId = createShader(vsCode, ShaderTypeVertex);
    GLuint fShaderId = createShader(fsCode, ShaderTypeFragment);
    
    m_programId = createProgram(vShaderId, fShaderId);
    
    /* 已成功链接到 Program 的 shader 可以移除 */
    removeShader(vShaderId, ShaderTypeVertex);
    removeShader(fShaderId, ShaderTypeFragment);
}

Shader::Shader(const GLchar* vCodePath, const GLchar* gCodePath, const GLchar* fCodePath)
{
    std::string vString;
    std::string gString;
    std::string fString;
    std::ifstream vsFile;
    std::ifstream gsFile;
    std::ifstream fsFile;
    /* 确保 ifstream 对象可以抛出异常 */
    vsFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    gsFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fsFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    
    /* 读取 GLSL */
    try
    {
        /* 打开文件 */
        vsFile.open(vCodePath);
        gsFile.open(gCodePath);
        fsFile.open(fCodePath);
        
        std::stringstream vsStream;
        std::stringstream gsStream;
        std::stringstream fsStream;
        
        /* 读取文件流 */
        vsStream << vsFile.rdbuf();
        gsStream << gsFile.rdbuf();
        fsStream << fsFile.rdbuf();
        
        /* 关闭文件 */
        vsFile.close();
        gsFile.close();
        fsFile.close();
        
        /* 文件流转换成 String 字符串 */
        vString = vsStream.str();
        gString = gsStream.str();
        fString = fsStream.str();
    }
    catch (std::ifstream::failure e)
    {
        std::cout << "读取 GLSL 文件失败！" << std::endl;
    }
    
    /* String 字符串转换成 const GLchar* */
    const GLchar* vsCode = vString.c_str();
    const GLchar* gsCode = gString.c_str();
    const GLchar* fsCode = fString.c_str();
    
    GLuint vShaderId = createShader(vsCode, ShaderTypeVertex);
    GLuint gShaderId = createShader(gsCode, ShaderTypeGeometry);
    GLuint fShaderId = createShader(fsCode, ShaderTypeFragment);
    
    m_programId = createProgram(vShaderId, gShaderId, fShaderId);
    
    /* 已成功链接到 Program 的 shader 可以移除 */
    removeShader(vShaderId, ShaderTypeVertex);
    removeShader(gShaderId, ShaderTypeGeometry);
    removeShader(fShaderId, ShaderTypeFragment);
}

#pragma mark -- 析构函数
Shader::~Shader()
{
//    removeShader(m_programId, Shader_program);
}

#pragma mark -- 设置 uniform(bool 类型) 的值
void Shader::setUniformBool(const std::string &name, bool value) const
{
    setUniformInt(name, (GLint)value);
}

#pragma mark -- 设置 uniform(int 类型) 的值
void Shader::setUniformInt(const std::string &name, GLint v1) const
{
    glUniform1i(uniformLocation(name), v1);
}

#pragma mark -- 设置 uniform(float 类型) 的值
void Shader::setUniformFloat(const std::string &name, GLfloat v1) const
{
    glUniform1f(uniformLocation(name), v1);
}

void Shader::setUniformVec2(const std::string &name, const glm::vec2 &value) const
{
    glUniform2fv(uniformLocation(name), 1, &value[0]);
}

void Shader::setUniformVec2(const std::string &name, GLfloat x, GLfloat y) const
{
    glUniform2f(uniformLocation(name), x, y);
}

void Shader::setUniformVec3(const std::string &name, const glm::vec3 &value) const
{
    glUniform3fv(uniformLocation(name), 1, &value[0]);
}

void Shader::setUniformVec3(const std::string &name, GLfloat x, GLfloat y, GLfloat z) const
{
    glUniform3f(uniformLocation(name), x, y, z);
}

void Shader::setUniformVec4(const std::string &name, const glm::vec4 &value) const
{
    glUniform4fv(uniformLocation(name), 1, &value[0]);
}

void Shader::setUniformVec4(const std::string &name, GLfloat x, GLfloat y, GLfloat z, GLfloat w) const
{
    glUniform4f(uniformLocation(name), x, y, z, w);
}

#pragma mark -- 设置 uniform(Matrix 类型) 的值
void Shader::setUniformMat2(const std::string &name, const glm::mat2 &mat) const
{
    setUniformMat2(name, &mat[0][0]);
}

void Shader::setUniformMat2(const std::string &name, const GLfloat* value) const
{
    glUseProgram(m_programId);
    glUniformMatrix2fv(uniformLocation(name), 1, GL_FALSE, value);
}

void Shader::setUniformMat3(const std::string &name, const glm::mat3 &mat) const
{
    setUniformMat3(name, &mat[0][0]);
}

void Shader::setUniformMat3(const std::string &name, const GLfloat* value) const
{
    glUniformMatrix3fv(uniformLocation(name), 1, GL_FALSE, value);
}

void Shader::setUniformMat4(const std::string &name, const glm::mat4 &mat) const
{
    setUniformMat4(name, &mat[0][0]);
}

void Shader::setUniformMat4(const std::string &name, const GLfloat* value) const
{
    glUniformMatrix4fv(uniformLocation(name), 1, GL_FALSE, value);
}

void Shader::setUniformBlockToPoint(const std::string &name, GLuint bindingPoint)
{
    glUniformBlockBinding(m_programId, uniformBlockIndex(name), bindingPoint);
}

#pragma mark -- 获取着色器程序对象 ID
GLuint Shader::programId()
{
    return m_programId;
}

#pragma mark -- 激活着色器程序
void Shader::use() const
{
    glUseProgram(m_programId);
}


#pragma mark - Private
#pragma mark -- 创建着色器
GLuint Shader::createShader(const GLchar* shaderCode, ShaderType sType) const
{
    if (NULL == shaderCode)
    {
        std::cout << "无法创建着色器！" << std::endl;
        return 0;
    }
    
    /* 声明一个着色器对象引用 ID */
    GLuint shaderId;
    switch (sType)
    {
        case ShaderTypeVertex:
            /* 创建 着色器（指明是顶点着色器） */
            shaderId = glCreateShader(GL_VERTEX_SHADER);
            break;
#ifdef ANDROID
        case ShaderTypeGeometry:
            /* 创建 着色器（指明是几何着色器） */
            shaderId = glCreateShader(GL_GEOMETRY_SHADER);
            break;
#endif
        case ShaderTypeFragment:
            /* 创建 着色器（指明是片段着色器） */
            shaderId = glCreateShader(GL_FRAGMENT_SHADER);
            break;
            
        default:
            shaderId = 0;
            break;
    }

    glShaderSource(shaderId, 1, &shaderCode, NULL);
    glCompileShader(shaderId);
    
    std::string type = sType == ShaderTypeVertex ? "VERTEX" : "FRAGMENT";
    checkCompileErrors(shaderId, type);
    
    return shaderId;
}

#pragma mark -- 创建着色器程序
GLuint Shader::createProgram(GLuint vShaderId, GLuint fShaderId) const
{
    if (0 == vShaderId || 0 == fShaderId)
    {
        std::cout << "无法创建着色器程序！" << std::endl;
        return 0;
    }
    
    GLuint programId;
    programId = glCreateProgram();
    if ( 0 == programId) return 0;
    
    glAttachShader(programId, vShaderId);
    glAttachShader(programId, fShaderId);
    
    glLinkProgram(programId);
    checkCompileErrors(programId,"PROGRAM");
    
    return programId;
}

GLuint Shader::createProgram(GLuint vShaderId, GLuint gShaderId, GLuint fShaderId) const
{
    if (0 == vShaderId || 0 == gShaderId || 0 == fShaderId)
    {
        std::cout << "无法创建着色器程序！" << std::endl;
        return 0;
    }
    GLuint programId;
    programId = glCreateProgram();
    if ( 0 == programId) return 0;
    
    glAttachShader(programId, vShaderId);
    glAttachShader(programId, gShaderId);
    glAttachShader(programId, fShaderId);
    
    glLinkProgram(programId);
    checkCompileErrors(programId,"PROGRAM");
    
    return programId;
}

#pragma mark -- 获取 Uniform 变量 地址
GLint Shader::uniformLocation(const std::string &name) const
{
    if (name.empty() || 0 == m_programId)
    {
        return -1;
    }
    GLint location = glGetUniformLocation(m_programId, name.c_str());
    return location;
}

#pragma mark -- 获取 uniform-block 变量索引
GLuint Shader::uniformBlockIndex(const std::string &name) const
{
    if (name.empty() || 0 == m_programId)
    {
        return 0;
    }
    GLuint ubIndex = glGetUniformBlockIndex(m_programId, name.c_str());
    return ubIndex;
}

#pragma mark -- 移除着色器
void Shader::removeShader(GLuint shaderId, ShaderType sType) const
{
    switch (sType)
    {
        case ShaderTypeVertex:
            /* 释放着色器对象 */
            glDeleteShader(shaderId);
            break;
            
        case ShaderTypeGeometry:
            /* 释放着色器对象 */
            glDeleteShader(shaderId);
            break;
            
        case ShaderTypeFragment:
            /* 释放着色器对象 */
            glDeleteShader(shaderId);
            break;
            
        default:
            break;
    }
}

void Shader::deleteProgram() const {
    glDeleteProgram(m_programId);
}

#pragma mark -- 检查着色器是否出错
// utility function for checking shader compilation/linking errors.
// ------------------------------------------------------------------------
bool Shader::checkCompileErrors(GLuint shader, std::string type) const
{
    GLint success;
    GLchar infoLog[1024];
    if (type != "PROGRAM")
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
    else
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
    return success;
}


