#ifndef __CUBE_H__
#define __CUBE_H__

#include <vector>

#include <GL/glew.h>

#include <tletc/types.h>
#include <tletc/renderer/mesh.h>
#include <tletc/system/meshregistry.h>
#include "entity.h"

static const Vertex cubeVertices[] = {
    // Front
    {{-0.5f,  0.5f, 0.5f, 1.0f}, {0.0f, 0.0f, 1.0f}},
    {{ 0.5f,  0.5f, 0.5f, 1.0f}, {0.0f, 0.0f, 1.0f}},
    {{ 0.5f, -0.5f, 0.5f, 1.0f}, {0.0f, 0.0f, 1.0f}},
    {{-0.5f, -0.5f, 0.5f, 1.0f}, {0.0f, 0.0f, 1.0f}},

    // Right
    {{0.5f,  0.5f,  0.5f, 1.0f}, {1.0f, 0.0f, 0.0f}},
    {{0.5f,  0.5f, -0.5f, 1.0f}, {1.0f, 0.0f, 0.0f}},
    {{0.5f, -0.5f, -0.5f, 1.0f}, {1.0f, 0.0f, 0.0f}},
    {{0.5f, -0.5f,  0.5f, 1.0f}, {1.0f, 0.0f, 0.0f}},

    // Back
    {{ 0.5f,  0.5f, -0.5f, 1.0f}, {0.0f, 0.0f, -1.0f}},
    {{-0.5f,  0.5f, -0.5f, 1.0f}, {0.0f, 0.0f, -1.0f}},
    {{-0.5f, -0.5f, -0.5f, 1.0f}, {0.0f, 0.0f, -1.0f}},
    {{ 0.5f, -0.5f, -0.5f, 1.0f}, {0.0f, 0.0f, -1.0f}},

    // Left
    {{-0.5f,  0.5f, -0.5f, 1.0f}, {-1.0f, 0.0f, 0.0f}},
    {{-0.5f,  0.5f,  0.5f, 1.0f}, {-1.0f, 0.0f, 0.0f}},
    {{-0.5f, -0.5f,  0.5f, 1.0f}, {-1.0f, 0.0f, 0.0f}},
    {{-0.5f, -0.5f, -0.5f, 1.0f}, {-1.0f, 0.0f, 0.0f}},

    // Top
    {{-0.5f,  0.5f,  0.5f, 1.0f}, {0.0f, 1.0f, 0.0f}},
    {{ 0.5f,  0.5f,  0.5f, 1.0f}, {0.0f, 1.0f, 0.0f}},
    {{ 0.5f,  0.5f, -0.5f, 1.0f}, {0.0f, 1.0f, 0.0f}},
    {{-0.5f,  0.5f, -0.5f, 1.0f}, {0.0f, 1.0f, 0.0f}},

    // Bottom
    {{-0.5f, -0.5f,  0.5f, 1.0f}, {0.0f, -1.0f, 0.0f}},
    {{ 0.5f, -0.5f,  0.5f, 1.0f}, {0.0f, -1.0f, 0.0f}},
    {{ 0.5f, -0.5f, -0.5f, 1.0f}, {0.0f, -1.0f, 0.0f}},
    {{-0.5f, -0.5f, -0.5f, 1.0f}, {0.0f, -1.0f, 0.0f}}
}; 
static const int cubeNumVertices = 24;

static const GLint cubeIndices[] = {
    3,  1,  0,  2,  1,  3,
    7,  5,  4,  6,  5,  7,
    11, 9,  8,  10, 9,  11,
    15, 13, 12, 14, 13, 15,
    16, 17, 19, 19, 17, 18,
    23, 21, 20, 22, 21, 23
};
static const int cubeNumIndices = 36;

static const std::vector<glm::vec2> cubeDefaultTexCoords = {
    {0, 1}, {1, 1}, {1, 0}, {0, 0},
    {0, 1}, {1, 1}, {1, 0}, {0, 0},
    {0, 1}, {1, 1}, {1, 0}, {0, 0},
    {0, 1}, {1, 1}, {1, 0}, {0, 0},
    {0, 1}, {1, 1}, {1, 0}, {0, 0},
    {0, 1}, {1, 1}, {1, 0}, {0, 0}
};

static const std::vector<glm::vec2> cubeLemonSquareTexCoords = {
    {0.0f, 1.0f}, {1.0f, 1.0f}, {1.0f, 0.5f}, {0.0f, 0.5f},
    {0.0f, 1.0f}, {1.0f, 1.0f}, {1.0f, 0.5f}, {0.0f, 0.5f},
    {0.0f, 1.0f}, {1.0f, 1.0f}, {1.0f, 0.5f}, {0.0f, 0.5f},
    {0.0f, 1.0f}, {1.0f, 1.0f}, {1.0f, 0.5f}, {0.0f, 0.5f},
    {0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 0.5f}, {0.0f, 0.5f},
    {0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 0.5f}, {0.0f, 0.5f},
};

class Cube : public Entity {
public:
    Cube(byte materialId) {
        if(m_cubeMeshId == 0xFF) {
            Mesh *cubeMesh = new Mesh(std::vector<Vertex>(cubeVertices, cubeVertices + cubeNumVertices), std::vector<GLint>(cubeIndices, cubeIndices + cubeNumIndices));
            m_cubeMeshId = cubeMesh->getId();

            MeshRegistry *registry = MeshRegistry::getRegistry();
            registry->registerMesh(cubeMesh);
        }

        p_meshId = m_cubeMeshId;
        p_materialId = materialId;
    }

    ~Cube() {}

private:
    static byte m_cubeMeshId;
};

// Initalize to sentinal 255 as it's greater than the max number of meshes (128)
byte Cube::m_cubeMeshId = 0xFF;

#endif