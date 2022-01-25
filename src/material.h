#ifndef __MATERIAL_H__
#define __MATERIAL_H__

#include <GL/glew.h>
#include <glm/vec4.hpp>

#include "types.h"

class Material {
public:
    ~Material();

    byte getId() const;

protected:
    Material();

private:
    byte m_matId;

    static byte s_nextId;
};

using MaterialRef = std::shared_ptr<Material>;

class PhongMaterial : public Material {
public:
    PhongMaterial(const glm::vec4 &ambientColor, float ka, const glm::vec4 &diffuseColor, float kd, const glm::vec4 &specularColor, float ks, float se);
    ~PhongMaterial();

    const glm::vec4 &getAmbientColor();
    const glm::vec4 &getDiffuseColor();
    const glm::vec4 &getSpecularColor();

    float getKa();
    float getKd();
    float getKs();
    float getSe();

private:
    glm::vec4 m_ambientColor;
    glm::vec4 m_diffuseColor;
    glm::vec4 m_specularColor;

    float m_ka;
    float m_kd;
    float m_ks;
    float m_se;
};

class TexMaterial : public Material {
public:
    TexMaterial(const char *filename, int channels, float ka, float kd, float ks, float se);
    ~TexMaterial();

    GLuint getTextureObjectId() const;

    float getKa() const;
    float getKd() const;
    float getKs() const;
    float getSe() const;

private:
    GLuint m_textureObjectId;

    float m_ka;
    float m_kd;
    float m_ks;
    float m_se;
};

#endif