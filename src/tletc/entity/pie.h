#ifndef __PIE_H__
#define __PIE_H__

#include <vector>

#include <GL/glew.h>
#include <glm/vec2.hpp>

#include <tletc/types.h>
#include <tletc/renderer/mesh.h>
#include <tletc/system/meshregistry.h>
#include "entity.h"

static const Vertex piesliceVertices[] = {
    {{-0.5f,  0.1f,  0.0f, 1.0f}, {0.0f,  1.0f, 0.0f}},
    {{ 0.0f,  0.1f, -0.5f, 1.0f}, {0.0f,  1.0f, 0.0f}},
    {{ 0.0f,  0.1f,  0.5f, 1.0f}, {0.0f,  1.0f, 0.0f}},

    {{ 0.0f,  0.1f, -0.5f, 1.0f}, {1.0f, 0.0f, 0.0f}},
    {{ 0.0f,  0.1f,  0.5f, 1.0f}, {1.0f, 0.0f, 0.0f}},
    {{ 0.0f, -0.1f,  0.5f, 1.0f}, {1.0f, 0.0f, 0.0f}},
    {{ 0.0f, -0.1f, -0.5f, 1.0f}, {1.0f, 0.0f, 0.0f}},

    {{-0.5f,  0.1f,  0.0f, 1.0f}, {-0.707107f, 0.0f, -0.707107f}},
    {{ 0.0f,  0.1f, -0.5f, 1.0f}, {-0.707107f, 0.0f, -0.707107f}},
    {{ 0.0f, -0.1f, -0.5f, 1.0f}, {-0.707107f, 0.0f, -0.707107f}},
    {{-0.5f, -0.1f,  0.0f, 1.0f}, {-0.707107f, 0.0f, -0.707107f}},

    {{ 0.0f,  0.1f,  0.5f, 1.0f}, {-0.707107f, 0.0f,  0.707107f}},
    {{-0.5f,  0.1f,  0.0f, 1.0f}, {-0.707107f, 0.0f,  0.707107f}},
    {{-0.5f, -0.1f,  0.0f, 1.0f}, {-0.707107f, 0.0f,  0.707107f}},
    {{ 0.0f, -0.1f,  0.5f, 1.0f}, {-0.707107f, 0.0f,  0.707107f}},

    {{-0.5f, -0.1f,  0.0f, 1.0f}, {0.0f, -1.0f, 0.0f}},
    {{ 0.0f, -0.1f, -0.5f, 1.0f}, {0.0f, -1.0f, 0.0f}},
    {{ 0.0f, -0.1f,  0.5f, 1.0f}, {0.0f, -1.0f, 0.0f}}
};
static const int piesliceNumVertices = 18;

static const GLint piesliceIndices[] = {
    2,  1,  0,
    3,  4,  6,  6,  4,  5,
    7,  8,  9,  7,  9,  10,
    11, 12, 13, 13, 14, 11,
    17, 16, 15
};
static const int piesliceNumIndices = 24;

static const std::vector<glm::vec2> napkinTexCoords = {
    {0.0f, 0.0f}, {0.0f, 1.0f}, {1.0f, 0.0f},
    {0.8f, 1.0f}, {0.8f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f},
    {0.8f, 1.0f}, {0.8f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f},
    {0.8f, 1.0f}, {0.8f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f},
    {0.0f, 0.0f}, {0.0f, 1.0f}, {1.0f, 0.0f}
};

class PieSlice : public Entity {
public:
    PieSlice(byte materialId) {
        if(m_piesliceMeshId == 0xFF) {
            Mesh *piesliceMesh = new Mesh(std::vector<Vertex>(piesliceVertices, piesliceVertices + piesliceNumVertices), std::vector<GLint>(piesliceIndices, piesliceIndices + piesliceNumIndices));
            m_piesliceMeshId = piesliceMesh->getId();

            MeshRegistry *registry = MeshRegistry::getRegistry();
            registry->registerMesh(piesliceMesh);
        }

        p_meshId = m_piesliceMeshId;
        p_materialId = materialId;
    }

    ~PieSlice() {}

private:
    static byte m_piesliceMeshId;
};

// Initalize to sentinal 255 as it's greater than the max number of meshes (128)
byte PieSlice::m_piesliceMeshId = 0xFF;

#endif