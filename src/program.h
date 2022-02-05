#ifndef __PROGRAM_H__
#define __PROGRAM_H__

#include <vector>
#include <string>

#include <GL/glew.h>
#include <glm/mat4x4.hpp>

#include "entity.h"
#include "material.h"

class ShaderProgram {
public:
    ShaderProgram(const std::string &friendlyName, const std::string &vertexPath, const std::string &fragmentPath);
    ~ShaderProgram();

    bool load();
    void use();
    void unuse();

    bool isLoaded();
    bool isInUse();

    template<typename T> bool setUniform(const char *name, const T &value);

    bool setEntityUniforms(Entity &entity);
    bool setEntityUniforms(std::vector<Entity> &entities);

private:
    template<typename T> inline void setUniformGlCall(GLint location, const T &value);

    bool setEntityUniformsGeneral(Entity &entity);
    virtual bool setEntityUniformsSpecalized(Entity &entity) = 0;

    GLuint m_programId;

    std::string m_friendlyName;
    std::string m_vertexPath;
    std::string m_fragmentPath;

    bool m_isLoaded;
    bool m_isInUse;
};

class PhongShader : public ShaderProgram {
public:
    PhongShader(const std::string &friendlyName, const std::string &vertexPath, const std::string &fragmentPath);
    ~PhongShader();

private:
    virtual bool setEntityUniformsSpecalized(Entity &entity);
};

class TexShader : public ShaderProgram {
public:
    TexShader(const std::string &friendlyName, const std::string &vertexPath, const std::string &fragmentPath);
    ~TexShader();

private:
    virtual bool setEntityUniformsSpecalized(Entity &entity);
};

#endif