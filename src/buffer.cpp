
#include "buffer.h"

#include <cstring>

#include "error.h"
#include "meshregistry.h"
#include "materialregistry.h"

ArrayBuffer::ArrayBuffer() :
    m_isFinalized(false),
    m_numVertices(0),
    m_numIndices(0),
    m_numEntities(0)
{
    GL_CALL(glCreateVertexArrays(1, &m_vao));
    GL_CALL(glCreateBuffers(1, &m_vbo));
    GL_CALL(glCreateBuffers(1, &m_ebo));
}

ArrayBuffer::~ArrayBuffer() {}

bool ArrayBuffer::addEntity(const Entity &entity) {
    if(m_isFinalized) {
        return false;
    }

    if(m_numEntities >= BUFF_MAX_ENTITIES) {
        return false;
    }
    
    MeshRegistry *registry = MeshRegistry::getRegistry();
    byte meshId = entity.getMeshId();
    MeshRef mesh = registry->getMesh(meshId);

    m_numVertices += mesh->getVertices().size();
    m_numIndices += mesh->getIndices().size();

    m_storedEntities.push_back(entity);

    m_numEntities++;

    return true;
}

bool ArrayBuffer::addEntities(const std::vector<Entity> &entities) {
    bool result = true;

    for(std::vector<Entity>::const_iterator i = entities.begin(); i != entities.end(); i++) {
        if(!addEntity(*i)) {
            result = false;
        }
    }

    return result;
}

bool ArrayBuffer::finalize() {
    using EntityIterator = std::vector<Entity>::iterator;

    if(m_isFinalized) {
        return false;
    }

    // Allocate the data store for the vertices
    // vertex data + texture coords + entityIds + materialIds
    GL_CALL(glNamedBufferData(m_vbo, m_numVertices * sizeof(Vertex) + m_numVertices * sizeof(glm::vec2) + m_numVertices * sizeof(byte) + m_numVertices * sizeof(byte), (void *) NULL, GL_STATIC_DRAW));
    // Allocate the data store for the indices
    GL_CALL(glNamedBufferData(m_ebo, m_numIndices * sizeof(GLint), (void *) NULL, GL_STATIC_DRAW));

    MeshRegistry *meshRegistry         = MeshRegistry::getRegistry();
    MaterialRegistry *materialRegistry = MaterialRegistry::getRegistry();

    float *texCoordsBuffer   = (float *) malloc(m_numVertices * sizeof(glm::vec2));
    byte *entityIdsBuffer    = (byte *) malloc(m_numVertices);
    GLint *meshIndicesBuffer = (GLint *) malloc(m_numIndices * sizeof(GLint));

    long currentVertexOffset = 0;
    long currentIndexOffset = 0;

    MeshRef currentMesh;
    MaterialRef currentMaterial;
    long currentNumVertices;
    long currentNumIndices;

    for(EntityIterator entityIterator = m_storedEntities.begin(); entityIterator != m_storedEntities.end(); entityIterator++) {
        currentMesh         = meshRegistry->getMesh(entityIterator->getMeshId());
        currentMaterial     = materialRegistry->getMaterial(entityIterator->getMaterialId());
        const std::vector<Vertex> &currentMeshVertices = currentMesh->getVertices();
        const std::vector<GLint>  &currentMeshIndices  = currentMesh->getIndices();
        currentNumVertices  = currentMeshVertices.size();
        currentNumIndices   = currentMeshIndices.size();

        // Buffer the main vertex data
        GL_CALL(glNamedBufferSubData(m_vbo, currentVertexOffset * sizeof(Vertex), currentNumVertices * sizeof(Vertex), (void *) currentMeshVertices.data()));

        if(entityIterator->hasTextureCoords()) {
            GL_CALL(glNamedBufferSubData(m_vbo, m_numVertices * sizeof(Vertex) + currentVertexOffset * sizeof(glm::vec2), currentNumVertices * sizeof(glm::vec2), (void *) entityIterator->getTextureCoords().data()));
        }
        // What happens if I don't buffer some of it

        // Buffer the vertices' entity ids
        memset(entityIdsBuffer, entityIterator->getEntityId(), currentNumVertices);
        GL_CALL(glNamedBufferSubData(m_vbo, m_numVertices * sizeof(Vertex) + m_numVertices * sizeof(glm::vec2) + currentVertexOffset, currentNumVertices, entityIdsBuffer));

        // Buffer the vertices' material ids
        memset(entityIdsBuffer, entityIterator->getMaterialId(), currentNumVertices);
        GL_CALL(glNamedBufferSubData(m_vbo, m_numVertices * sizeof(Vertex) + m_numVertices * sizeof(glm::vec2) + m_numVertices * sizeof(byte) + currentVertexOffset, currentNumVertices, entityIdsBuffer));

        // First offset the mesh's indices by the number of vertices already in the buffer
        // Then buffer indices
        memcpy(meshIndicesBuffer, currentMeshIndices.data(), currentNumIndices * sizeof(GLint));
        for(int j = 0; j < currentNumIndices; j++) {
            meshIndicesBuffer[j] += currentVertexOffset;
        }
        GL_CALL(glNamedBufferSubData(m_ebo, currentIndexOffset * sizeof(GLint), currentNumIndices * sizeof(GLint), meshIndicesBuffer));

        currentVertexOffset += currentNumVertices;
        currentIndexOffset  += currentNumIndices;
    }

    free(meshIndicesBuffer);
    free(entityIdsBuffer);
    free(texCoordsBuffer);

    setVertexAttributes();

    m_isFinalized = true;

    return true;
}

void ArrayBuffer::bind() {
    GL_CALL(glBindVertexArray(m_vao));
    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, m_vbo));
    GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo));
}

void ArrayBuffer::unbind() {
    GL_CALL(glBindVertexArray(0));
    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, 0));
    GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

long ArrayBuffer::getNumVertices() {
    return m_numVertices;
}

long ArrayBuffer::getNumIndices() {
    return m_numIndices;
}

bool ArrayBuffer::isFinalized() {
    return m_isFinalized;
}

void ArrayBuffer::setVertexAttributes() {
    GLint previousVao;
    GLint previousVbo;
    GL_CALL(glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &previousVao));
    GL_CALL(glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &previousVbo));

    GL_CALL(glBindVertexArray(m_vao));
    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, m_vbo));

    // Vertex Position
    GL_CALL(glEnableVertexAttribArray(0));
    GL_CALL(glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) 0));

    // Vertex Normal
    GL_CALL(glEnableVertexAttribArray(1));
    GL_CALL(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) (4 * sizeof(GLfloat))));

    // Vertex Tex Coords
    GL_CALL(glEnableVertexAttribArray(2));
    GL_CALL(glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void *) (m_numVertices * sizeof(Vertex))));

    // Vertex entityId
    GL_CALL(glEnableVertexAttribArray(3));
    GL_CALL(glVertexAttribIPointer(3, 1, GL_UNSIGNED_BYTE, 0, (void *) (m_numVertices * sizeof(Vertex) + m_numVertices * sizeof(glm::vec2))));

    // Vertex materialId
    GL_CALL(glEnableVertexAttribArray(4));
    GL_CALL(glVertexAttribIPointer(4, 1, GL_UNSIGNED_BYTE, 0, (void *) (m_numVertices * sizeof(Vertex) + m_numVertices * sizeof(glm::vec2) + m_numVertices * sizeof(byte))));

    GL_CALL(glBindVertexArray(previousVao));
    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, previousVbo));
}