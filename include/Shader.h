#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>


class Shader {
public:
    
    // constructor reads and builds the shader
    Shader(const char* vertexPath, const char* fragmentPath);
    // use/activate the shader
    void use();
    // utility uniform functions
    void setBool(const std::string& name, bool value) const;
    void setInt(const std::string& name, int value) const;
    void setFloat(const std::string& name, float value) const;
    void setVec4(const std::string& name, float value, float value2, float value3, float value4) const;
    void setMat4(const std::string& name, glm::mat4 value) const;

private:

    // the program ID
    unsigned int ID;
};