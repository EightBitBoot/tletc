
#include "program.h"

#include <stdio.h>
#include <stdlib.h>

#include <string>

#include "error.h"
#include "material.h"
#include "materialregistry.h"

// --------------- Static Functions ---------------

static GLuint setupShader(std::string &filepath, GLenum shaderType, std::string &friendlyName) {
    GLuint shaderId = 0;

    FILE *shaderFile = nullptr;
    long shaderFileLen = 0;
    char *shaderBuffer = nullptr;

    shaderFile = fopen(filepath.c_str(), "rt");
    if(!shaderFile) {
        perror("open shaderFile");
        return 0;
    }

    fseek(shaderFile, 0, SEEK_END); 
    shaderFileLen = ftell(shaderFile);
    fseek(shaderFile, 0, SEEK_SET); 

    shaderBuffer = (char *) malloc(shaderFileLen + 1);
    shaderBuffer[shaderFileLen] = 0; // Set the null terminator
    fread(shaderBuffer, shaderFileLen, 1, shaderFile);
    fclose(shaderFile);

    shaderId = GL_CALL(glCreateShader(shaderType));

    GL_CALL(glShaderSource(shaderId, 1, &shaderBuffer, NULL));

    free(shaderBuffer);

    GL_CALL(glCompileShader(shaderId));
    GLint compilationStatus;
    GL_CALL(glGetShaderiv(shaderId, GL_COMPILE_STATUS, &compilationStatus));
    if(compilationStatus == GL_FALSE) {
        GLint logLen = 0;
        GL_CALL(glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &logLen));

        GLchar *log = (GLchar *) malloc(logLen);
        GL_CALL(glGetShaderInfoLog(shaderId, logLen, NULL, log));

        const char *shaderTypeName = (shaderType == GL_VERTEX_SHADER ? "vertex" : "fragment");
        fprintf(stderr, "Error compiling %s shader in program \"%s\":\n%s\n", shaderTypeName, friendlyName.c_str(), log);

        free(log);
        GL_CALL(glDeleteShader(shaderId));
        shaderId = 0;
    }

    return shaderId;
}

static GLuint setupProgram(std::string &vertFile, std::string &fragFile, std::string &friendlyName) {
    GLuint vertShader = setupShader(vertFile, GL_VERTEX_SHADER, friendlyName); 
    if(!vertShader) {
        return 0;
    }

    GLuint fragShader = setupShader(fragFile, GL_FRAGMENT_SHADER, friendlyName); 
    if(!fragShader) {
        return 0;
    }

    GLint program = GL_CALL(glCreateProgram());
    GL_CALL(glAttachShader(program, vertShader));
    GL_CALL(glAttachShader(program, fragShader));
    
    GL_CALL(glLinkProgram(program));
    GLint linkStatus;
    GL_CALL(glGetProgramiv(program, GL_LINK_STATUS, &linkStatus));

    GL_CALL(glDetachShader(program, vertShader));
    GL_CALL(glDetachShader(program, fragShader));

    GL_CALL(glDeleteShader(vertShader));
    GL_CALL(glDeleteShader(fragShader));

    if(linkStatus == GL_FALSE) {
        GLint logLen = 0;
        GL_CALL(glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLen));

        GLchar *log = (GLchar *) malloc(logLen);
        GL_CALL(glGetProgramInfoLog(program, logLen, NULL, log));

        fprintf(stderr, "Error linking program\"%s\":\n%s\n", friendlyName.c_str(), log);

        free(log);
        glDeleteProgram(program);
        program = 0;
    }

    return program;
}

// --------------- ShaderProgram ---------------

ShaderProgram::ShaderProgram(const std::string &friendlyName, const std::string &vertexPath, const std::string &fragmentPath) :
    m_programId(0),
    m_friendlyName(friendlyName),
    m_vertexPath(vertexPath),
    m_fragmentPath(fragmentPath),

    m_isLoaded(false),
    m_isInUse(false)
{}

ShaderProgram::~ShaderProgram() {}

bool ShaderProgram::load() {
    GLuint oldProgramId = m_programId;

    m_programId = setupProgram(m_vertexPath, m_fragmentPath, m_friendlyName);

    if(!m_programId) {
        // Failed to load program
        m_isLoaded = false;
        return false;
    }

    if(oldProgramId) {
        // Object previously held an OpenGL program: delete it
        GL_CALL(glDeleteProgram(oldProgramId));
    }

    if(m_isInUse) {
        // If the program was previously being used, use the new one
        GL_CALL(glUseProgram(m_programId));
    }

    return true;
}

void ShaderProgram::use() {
    GL_CALL(glUseProgram(m_programId));
    m_isInUse = true;
}

void ShaderProgram::unuse() {
    GL_CALL(glUseProgram(0));
    m_isInUse = false;
}

template<typename T>
bool ShaderProgram::setUniform(const char *name, const T& value) {
    GLint previousProgram;
    GL_CALL(glGetIntegerv(GL_CURRENT_PROGRAM, &previousProgram));

    GL_CALL(glUseProgram(m_programId));

    GLint location = GL_CALL(glGetUniformLocation(m_programId, name));
    if(location == -1) {
        fprintf(stderr, "Couldn't locate uniform \"%s\" in program \"%s\"!\n", name, m_friendlyName);
        return false;
    }

    setUniformGlCall<T>(location, value);

    GL_CALL(glUseProgram(previousProgram));

    return true;
}

template <>
inline void ShaderProgram::setUniformGlCall<int>(GLint location, const int &value) {
    GL_CALL(glUniform1i(location, value));
}

template <>
inline void ShaderProgram::setUniformGlCall<float>(GLint location, const float &value) {
    GL_CALL(glUniform1f(location, value));
}

template <>
inline void ShaderProgram::setUniformGlCall<glm::vec4>(GLint location, const glm::vec4 &value) {
    GL_CALL(glUniform4fv(location, 1, &value[0]));
} 

template <>
inline void ShaderProgram::setUniformGlCall<glm::mat4>(GLint location, const glm::mat4 &value) {
    GL_CALL(glUniformMatrix4fv(location, 1, GL_FALSE, &value[0][0]));
}

bool ShaderProgram::setEntityUniforms(Entity &entity) {
    bool generalSuccess = false;
    bool specalizedSuccess = false;

    generalSuccess = setEntityUniformsGeneral(entity);
    specalizedSuccess = setEntityUniformsSpecalized(entity);

    return generalSuccess && specalizedSuccess;
}

bool ShaderProgram::setEntityUniformsGeneral(Entity &entity) {
    bool modelSuccess  = false;
    bool normalSuccess = false;

    char modelMatrixStr[16] = {0};
    snprintf(modelMatrixStr, 16, "u_modelMats[%d]", entity.getEntityId());
    modelSuccess = setUniform<glm::mat4>(modelMatrixStr, entity.getModelMatrix());

    char normMatrixStr[15] = {0};
    snprintf(normMatrixStr, 15, "u_normMats[%d]", entity.getEntityId());
    normalSuccess = setUniform<glm::mat4>(normMatrixStr, entity.getNormalMatrix());

    return modelSuccess && normalSuccess;
}

bool ShaderProgram::setEntityUniforms(std::vector<Entity> &entities) {
    bool result = true;

    for(std::vector<Entity>::iterator i = entities.begin(); i != entities.end(); i++) {
        result = result && setEntityUniforms(*i);
    }

    return result;
}

bool ShaderProgram::isLoaded() { return m_isLoaded; }
bool ShaderProgram::isInUse() { return m_isInUse; }

// --------------- PhongShader ---------------

PhongShader::PhongShader(const std::string &friendlyName, const std::string &vertexPath, const std::string &fragmentPath) :
    ShaderProgram(friendlyName, vertexPath, fragmentPath)
{}

PhongShader::~PhongShader() {}

bool PhongShader::setEntityUniformsSpecalized(Entity &entity) {
    bool success = true;

    MaterialRegistry *materialRegistry = MaterialRegistry::getRegistry();
    PhongMaterial *entityMaterial = (PhongMaterial *) (materialRegistry->getMaterial(entity.getMaterialId()).get());
    char materialStructStr[16] = {0};
    snprintf(materialStructStr, 16, "u_materials[%d]", entity.getMaterialId());

    success = success && setUniform<glm::vec4>((std::string(materialStructStr) + ".ambientColor").c_str(),  entityMaterial->getAmbientColor());
    success = success && setUniform<glm::vec4>((std::string(materialStructStr) + ".diffuseColor").c_str(),  entityMaterial->getDiffuseColor());
    success = success && setUniform<glm::vec4>((std::string(materialStructStr) + ".specularColor").c_str(), entityMaterial->getSpecularColor());

    success = success && setUniform<float>((std::string(materialStructStr) + ".ka").c_str(), entityMaterial->getKa());
    success = success && setUniform<float>((std::string(materialStructStr) + ".kd").c_str(), entityMaterial->getKd());
    success = success && setUniform<float>((std::string(materialStructStr) + ".ks").c_str(), entityMaterial->getKs());
    success = success && setUniform<float>((std::string(materialStructStr) + ".se").c_str(), entityMaterial->getSe());

    return success;
}

// --------------- TexShader ---------------

TexShader::TexShader(const std::string &friendlyName, const std::string &vertexPath, const std::string &fragmentPath) :
    ShaderProgram(friendlyName, vertexPath, fragmentPath)
{}

TexShader::~TexShader() {}

bool TexShader::setEntityUniformsSpecalized(Entity &entity) {
    bool success = true;

    MaterialRegistry *materialRegistry = MaterialRegistry::getRegistry();    
    TexMaterial *entityMaterial = (TexMaterial *) (materialRegistry->getMaterial(entity.getMaterialId()).get());
    char materialStructStr[16] = {0};
    snprintf(materialStructStr, 16, "u_materials[%d]", entity.getMaterialId());

    GL_CALL(glActiveTexture(GL_TEXTURE0 + entityMaterial->getId()));
    GL_CALL(glBindTexture(GL_TEXTURE_2D, entityMaterial->getTextureObjectId()));

    success = success && setUniform<int>((std::string(materialStructStr) + ".texSampler").c_str(), entityMaterial->getId());

    success = success && setUniform<float>((std::string(materialStructStr) + ".ka").c_str(), entityMaterial->getKa());
    success = success && setUniform<float>((std::string(materialStructStr) + ".kd").c_str(), entityMaterial->getKd());
    success = success && setUniform<float>((std::string(materialStructStr) + ".ks").c_str(), entityMaterial->getKs());
    success = success && setUniform<float>((std::string(materialStructStr) + ".se").c_str(), entityMaterial->getSe());

    return success;
}