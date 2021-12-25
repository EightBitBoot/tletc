#ifndef __ENTITY_H__
#define __ENTITY_H__

#include <vector>

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

#include "types.h"

class Entity {
public:
    Entity(byte meshId, byte materialId);
    ~Entity();

    const glm::mat4 &getModelMatrix();
    const glm::mat4 &getNormalMatrix();

    bool isModelMatrixStale() const;

    bool hasTextureCoords() const;
    const std::vector<glm::vec2> &getTextureCoords() const;
    void setTextureCoords(const std::vector<glm::vec2> &textureCoords);

    byte getEntityId() const;
    byte getMeshId() const;
    byte getMaterialId() const;

    const glm::vec3 &getCoords() const;
    float getX() const;
    float getY() const;
    float getZ() const;

    const glm::vec3 &getRotation() const;
    float getRotationX() const;
    float getRotationY() const;
    float getRotationZ() const;

    const glm::vec3 &getScale() const;
    float getScaleX() const;
    float getScaleY() const;
    float getScaleZ() const;

    void setCoords(const glm::vec3 &coords);
    void setX(float x);
    void setY(float y);
    void setZ(float z);

    void translate(const glm::vec3 &translate);
    void translateX(float x);
    void translateY(float y);
    void translateZ(float z);

    void setRotation(const glm::vec3 &rotation);
    void setRotationX(float deg);
    void setRotationY(float deg);
    void setRotationZ(float deg);

    void rotateX(float deg);
    void rotateY(float deg);
    void rotateZ(float deg);

    void setScale(const glm::vec3 &rotation);
    void setScaleX(float factor);
    void setScaleY(float factor);
    void setScaleZ(float factor);

    void scaleX(float factor);
    void scaleY(float factor);
    void scaleZ(float factor);

protected:
    Entity(); // This is useful if the child class has to register the mesh before setting p_meshId
              // Child MUST set p_meshId

    byte p_meshId;
    byte p_materialId;

    std::vector<glm::vec2> p_textureCoords;

private:
    glm::vec3 m_coords;
    glm::vec3 m_rotation;
    glm::vec3 m_scale;

    byte m_entityId;
    static byte m_nextEntityId;

    glm::mat4 m_modelMatCache;
    glm::mat4 m_normalMatrixCache;
    bool m_isModelMatStale;
};

#endif