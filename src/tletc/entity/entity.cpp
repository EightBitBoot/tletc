
#include "entity.h"

#include <glm/gtx/transform.hpp>

byte Entity::m_nextEntityId = 0;

Entity::Entity(byte meshId, byte materialId) :
    m_coords(0.0f, 0.0f, 0.0f),
    m_rotation(0.0f, 0.0f, 0.0f),
    m_scale(1.0f, 1.0f, 1.0f),

    m_entityId(m_nextEntityId++),     // Increment m_nextEntityId for next entity created

    p_meshId(meshId),
    p_materialId(materialId),

    m_modelMatCache(1.0f),
    m_normalMatrixCache(1.0f),
    m_isModelMatStale(true)       // Model matrix always has to be genrated on the first call to getModelMatrix
{}

Entity::Entity() : Entity(0, 0) {}

Entity::~Entity() {}

const glm::mat4 &Entity::getModelMatrix() {
    if(m_isModelMatStale) {
        // Model matrix needs to be recalculated

        // Reset model matrix
        m_modelMatCache = glm::mat4(1.0f);

        // Finally translate the matrix
        m_modelMatCache = glm::translate(m_modelMatCache, m_coords);

        // Next rotate the matrix
        m_modelMatCache = glm::rotate(m_modelMatCache, glm::radians(m_rotation.z), glm::vec3(0.0f, 0.0f, 1.0f)); 
        m_modelMatCache = glm::rotate(m_modelMatCache, glm::radians(m_rotation.y), glm::vec3(0.0f, 1.0f, 0.0f)); 
        m_modelMatCache = glm::rotate(m_modelMatCache, glm::radians(m_rotation.x), glm::vec3(1.0f, 0.0f, 0.0f)); 

        // First scale the matrix
        m_modelMatCache = glm::scale(m_modelMatCache, m_scale);

        // Cache the normal matrix as well
        m_normalMatrixCache = glm::transpose(glm::inverse(m_modelMatCache));

        m_isModelMatStale = false;
    }

    return m_modelMatCache;
}

const glm::mat4 &Entity::getNormalMatrix() {
    if(m_isModelMatStale) {
        // Update both matricies
        getModelMatrix();
    }

    return m_normalMatrixCache;
}

bool Entity::hasTextureCoords() const { return p_textureCoords.size() > 0; }
const std::vector<glm::vec2> &Entity::getTextureCoords() const { return p_textureCoords; }
void Entity::setTextureCoords(const std::vector<glm::vec2> &textureCoords) { p_textureCoords = std::vector<glm::vec2>(textureCoords); }

bool Entity::isModelMatrixStale() const { return m_isModelMatStale; }

byte Entity::getEntityId() const { return m_entityId; }
byte Entity::getMeshId() const { return p_meshId; }
byte Entity::getMaterialId() const { return p_materialId; }

const glm::vec3 &Entity::getCoords() const { return m_coords; }
float Entity::getX() const { return m_coords.x; }
float Entity::getY() const { return m_coords.y; }
float Entity::getZ() const { return m_coords.z; }

const glm::vec3 &Entity::getRotation() const { return m_rotation; }
float Entity::getRotationX() const { return m_rotation.x; }
float Entity::getRotationY() const { return m_rotation.y; };
float Entity::getRotationZ() const { return m_rotation.z; };

const glm::vec3 &Entity::getScale() const { return m_scale; };
float Entity::getScaleX() const { return m_scale.x; };
float Entity::getScaleY() const { return m_scale.y; };
float Entity::getScaleZ() const { return m_scale.z; };

void Entity::setCoords(const glm::vec3 &coords) { m_coords = coords; m_isModelMatStale = true; }
void Entity::setX(float x) { m_coords.x = x; m_isModelMatStale = true; }
void Entity::setY(float y) { m_coords.y = y; m_isModelMatStale = true; }
void Entity::setZ(float z) { m_coords.z = z; m_isModelMatStale = true; }

void Entity::translate(const glm::vec3 &translate) { m_coords += translate; m_isModelMatStale = true; }
void Entity::translateX(float x) { m_coords.x += x; m_isModelMatStale = true; }
void Entity::translateY(float y) { m_coords.y += y; m_isModelMatStale = true; }
void Entity::translateZ(float z) { m_coords.z += z; m_isModelMatStale = true; }

void Entity::setRotation(const glm::vec3 &rotation) { m_rotation = rotation; m_isModelMatStale = true; }
void Entity::setRotationX(float deg) { m_rotation.x = deg; m_isModelMatStale = true; }
void Entity::setRotationY(float deg) { m_rotation.y = deg; m_isModelMatStale = true; }
void Entity::setRotationZ(float deg) { m_rotation.z = deg; m_isModelMatStale = true; }

void Entity::rotateX(float deg) { m_rotation.x += deg; m_isModelMatStale = true; }
void Entity::rotateY(float deg) { m_rotation.y += deg; m_isModelMatStale = true; }
void Entity::rotateZ(float deg) { m_rotation.z += deg; m_isModelMatStale = true; }

void Entity::setScale(const glm::vec3 &scale) { m_scale = scale; m_isModelMatStale = true; }
void Entity::setScaleX(float factor) { m_scale.x = factor; m_isModelMatStale = true; }
void Entity::setScaleY(float factor) { m_scale.y = factor; m_isModelMatStale = true; }
void Entity::setScaleZ(float factor) { m_scale.z = factor; m_isModelMatStale = true; }

void Entity::scaleX(float factor) { m_scale.x *= factor; m_isModelMatStale = true; }
void Entity::scaleY(float factor) { m_scale.y *= factor; m_isModelMatStale = true; }
void Entity::scaleZ(float factor) { m_scale.z *= factor; m_isModelMatStale = true; }