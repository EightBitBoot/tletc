#ifndef __QUAD_H__
#define __QUAD_H__

#include <vector>

#include <GL/glew.h>
#include <glm/vec2.hpp>

#include "types.h"
#include "entity.h"
#include "mesh.h"
#include "meshregistry.h"

static const Vertex quadVertices[] = {
    {{-0.5f,  0.5f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f}},
    {{ 0.5f,  0.5f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f}},
    {{ 0.5f, -0.5f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f}},
    {{-0.5f, -0.5f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f}}
};
static const int quadNumVertices = 4;

static const GLint quadIndices[] = {
    1, 0, 3, 1, 3, 2
};
static const int quadNumIndices = 6;

static const std::vector<glm::vec2> quadTexCoords = {
    {0, 1},
    {1, 1},
    {1, 0},
    {0, 0}
};

static const int guadNumIndices = 6;

class Quad : public Entity {
public:
    Quad(byte materialId) {
        if(m_quadMeshId == 0xFF) {
            Mesh *quadMesh = new Mesh(std::vector<Vertex>(quadVertices, quadVertices + quadNumVertices), std::vector<GLint>(quadIndices, quadIndices + quadNumIndices));
            m_quadMeshId = quadMesh->getId();

            MeshRegistry *registry = MeshRegistry::getRegistry();
            registry->registerMesh(quadMesh);
        } 

        p_meshId = m_quadMeshId;
        p_materialId = materialId;
        
        setTextureCoords(quadTexCoords);
    }

    ~Quad() {}

private:
    static byte m_quadMeshId;
};

byte Quad::m_quadMeshId = 0xFF;

#endif