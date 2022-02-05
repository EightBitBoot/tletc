#ifndef __BUFFER_H__
#define __BUFFER_H__

#include <vector>

#include <GL/glew.h>

#include <tletc/types.h>
#include <tletc/entity/entity.h>

#define BUFF_MAX_ENTITIES 64

typedef struct EntityIds_s {
    byte entityId;
    byte meshId;
    byte materialId;
} EntityIds;

class ArrayBuffer {
public:
    ArrayBuffer();
    ~ArrayBuffer();

    bool addEntity(const Entity &entity);
    bool addEntities(const std::vector<Entity> &entities);
    bool finalize();

    void bind();
    void unbind();

    long getNumVertices();
    long getNumIndices();
    bool isFinalized();

private:
    void setVertexAttributes();

    std::vector<Entity> m_storedEntities;
    long m_numVertices;
    long m_numIndices;
    int m_numEntities;

    bool m_isFinalized;

    GLuint m_vao;
    GLuint m_vbo;
    GLuint m_ebo;
};

#endif