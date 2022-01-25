
#include "material.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "error.h"
#include "types.h"

// --------------- Material ---------------

byte Material::s_nextId = 0;

Material::Material() :
    m_matId(s_nextId++)
{}

Material::~Material() {}

byte Material::getId() const { return m_matId; }

PhongMaterial::PhongMaterial(const glm::vec4 &ambientColor, float ka, const glm::vec4 &diffuseColor, float kd, const glm::vec4 &specularColor, float ks, float se) :
    m_ambientColor(ambientColor),
    m_diffuseColor(diffuseColor),
    m_specularColor(specularColor),

    m_ka(ka),
    m_kd(kd),
    m_ks(ks),
    m_se(se)
{}

// --------------- PhongMaterial ---------------

const glm::vec4 &PhongMaterial::getAmbientColor()  { return m_ambientColor; }
const glm::vec4 &PhongMaterial::getDiffuseColor()  { return m_diffuseColor; }
const glm::vec4 &PhongMaterial::getSpecularColor() { return m_specularColor; }

float PhongMaterial::getKa() { return m_ka; }
float PhongMaterial::getKd() { return m_kd; }
float PhongMaterial::getKs() { return m_ks; }
float PhongMaterial::getSe() { return m_se; }

// --------------- TexMaterial ---------------

TexMaterial::TexMaterial(const char *filename, int channels, float ka, float kd, float ks, float se) :
    m_ka(ka),
    m_kd(kd),
    m_ks(ks),
    m_se(se)
{
    int imageWidth = 0;
    int imageHeight = 0;
    byte *imageBuffer = NULL;

    GL_CALL(glGenTextures(1, &m_textureObjectId));
    GL_CALL(glBindTexture(GL_TEXTURE_2D, m_textureObjectId));

    stbi_set_flip_vertically_on_load(true);
    imageBuffer = stbi_load(filename, &imageWidth, &imageHeight, NULL, channels);
    if(imageBuffer == NULL) {
        fprintf(stderr, "Error loading image \"%s\": %s\n", filename, stbi_failure_reason());
        GL_CALL(glBindTexture(GL_TEXTURE_2D, 0));
        GL_CALL(glDeleteTextures(1, &m_textureObjectId));
        m_textureObjectId = 0;
    }

    if(m_textureObjectId != 0) {
        if(channels == 4) {
            // Texture has alpha channel
            GL_CALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageBuffer));
        }
        else {
            GL_CALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imageWidth, imageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, imageBuffer));
        }

        stbi_image_free(imageBuffer);

        GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
        GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));

        GL_CALL(glGenerateMipmap(GL_TEXTURE_2D));
        GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR));

        GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    }
}

TexMaterial::~TexMaterial() {}

GLuint TexMaterial::getTextureObjectId() const { return m_textureObjectId; }

float TexMaterial::getKa() const { return m_ka; }
float TexMaterial::getKd() const { return m_kd; }
float TexMaterial::getKs() const { return m_ks; }
float TexMaterial::getSe() const { return m_se; }