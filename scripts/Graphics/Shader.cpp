#include "Shader.h"

#include <iostream>
#include <fstream>
#include <sstream>

Shader::Shader(const std::string &vertexPath, const std::string &fragmentPath) {
    // Read shader files and store them as std::string (keep them alive)
    std::string vertexShaderCodeStr = readShaderFile(vertexPath);
    std::string fragmentShaderCodeStr = readShaderFile(fragmentPath);

    // Convert to C-style strings for OpenGL
    const char* vertexShaderCode = vertexShaderCodeStr.c_str();
    const char* fragmentShaderCode = fragmentShaderCodeStr.c_str();

    GLuint vertexShader, fragmentShader;

    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1 , &vertexShaderCode, NULL);
    glCompileShader(vertexShader);
    checkShaderCompileError(vertexShader, "VERTEX");

    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderCode, NULL);
    glCompileShader(fragmentShader);
    checkShaderCompileError(fragmentShader, "FRAGMENT");

    ID = glCreateProgram();
    glAttachShader(ID, vertexShader);
    glAttachShader(ID, fragmentShader);
    glLinkProgram(ID);
    checkShaderCompileError(ID, "PROGRAM");

    std::cout << "Opengl Shader : " << vertexPath << " Compiled Successfully " << std::endl;
    std::cout << "Opengl Shader : " << fragmentPath << " Compiled Successfully " << std::endl;

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Shader::use() {
    glUseProgram(ID);
}

void Shader::setBool(const std::string &name, bool value) const {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::setInt(const std::string &name, int value) const {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const std::string &name, float value) const {
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setVec3(const std::string &name, const glm::vec3 &value) const {
    glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}

void Shader::setMat4(const std::string &name, const glm::mat4 &mat) const {
    glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

std::string Shader::readShaderFile(const std::string &filePath) {
    std::string code;
    std::ifstream shaderFile;

    shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try {
        shaderFile.open(filePath);
        std::stringstream shaderStream;

        shaderStream << shaderFile.rdbuf();

        shaderFile.close();
        code = shaderStream.str();
    } catch (std::ifstream::failure& e) {
        std::cerr << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ\n" << std::endl;
    }

    return code;
}

void Shader::checkShaderCompileError(GLuint shader, const std::string& type) {
    GLint success;
    GLchar infoLog[1024];

    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (!success) {
        // Check for OpenGL errors before retrieving the log
        GLenum error = glGetError();
        if (error != GL_NO_ERROR) {
            std::cerr << "OpenGL error before glGetShaderInfoLog(): " << error << std::endl;
        }

        // Retrieve the shader compilation log
        glGetShaderInfoLog(shader, 1024, NULL, infoLog);
        std::cerr << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n"
                  << infoLog << "\n -- --------------------------------------------------- -- "
                  << std::endl;

        // Check for OpenGL errors after retrieving the log
        error = glGetError();
        if (error != GL_NO_ERROR) {
            std::cerr << "OpenGL error after glGetShaderInfoLog(): " << error << std::endl;
        }

        exit(-1);
    }
}


