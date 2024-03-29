#ifndef __CYLINDER_H__
#define __CYLINDER_H__

#include <vector>

#include <glm/vec2.hpp>
#include <GL/glew.h>

#include <tletc/types.h>
#include <tletc/renderer/mesh.h>
#include <tletc/system/meshregistry.h>
#include "entity.h"

static const Vertex cylinderVertices[] = {
    {{ 0.500000f, -0.500000f,  0.000000f, 1.0f}, { 0.500000f,  0.000000f,  0.000000f}},
    {{ 0.500000f,  0.500000f,  0.000000f, 1.0f}, { 0.500000f,  0.000000f,  0.000000f}},
    {{ 0.475528f, -0.500000f, -0.154508f, 1.0f}, { 0.475528f,  0.000000f, -0.154508f}},
    {{ 0.475528f,  0.500000f, -0.154508f, 1.0f}, { 0.475528f,  0.000000f, -0.154508f}},
    {{ 0.404508f, -0.500000f, -0.293893f, 1.0f}, { 0.404508f,  0.000000f, -0.293893f}},
    {{ 0.404508f,  0.500000f, -0.293893f, 1.0f}, { 0.404508f,  0.000000f, -0.293893f}},
    {{ 0.293893f, -0.500000f, -0.404508f, 1.0f}, { 0.293893f,  0.000000f, -0.404508f}},
    {{ 0.293893f,  0.500000f, -0.404508f, 1.0f}, { 0.293893f,  0.000000f, -0.404508f}},
    {{ 0.154508f, -0.500000f, -0.475528f, 1.0f}, { 0.154508f,  0.000000f, -0.475528f}},
    {{ 0.154508f,  0.500000f, -0.475528f, 1.0f}, { 0.154508f,  0.000000f, -0.475528f}},
    {{ 0.000000f, -0.500000f, -0.500000f, 1.0f}, { 0.000000f,  0.000000f, -0.500000f}},
    {{ 0.000000f,  0.500000f, -0.500000f, 1.0f}, { 0.000000f,  0.000000f, -0.500000f}},
    {{-0.154508f, -0.500000f, -0.475528f, 1.0f}, {-0.154508f,  0.000000f, -0.475528f}},
    {{-0.154508f,  0.500000f, -0.475528f, 1.0f}, {-0.154508f,  0.000000f, -0.475528f}},
    {{-0.293893f, -0.500000f, -0.404508f, 1.0f}, {-0.293893f,  0.000000f, -0.404508f}},
    {{-0.293893f,  0.500000f, -0.404508f, 1.0f}, {-0.293893f,  0.000000f, -0.404508f}},
    {{-0.404508f, -0.500000f, -0.293893f, 1.0f}, {-0.404508f,  0.000000f, -0.293893f}},
    {{-0.404508f,  0.500000f, -0.293893f, 1.0f}, {-0.404508f,  0.000000f, -0.293893f}},
    {{-0.475528f, -0.500000f, -0.154508f, 1.0f}, {-0.475528f,  0.000000f, -0.154508f}},
    {{-0.475528f,  0.500000f, -0.154508f, 1.0f}, {-0.475528f,  0.000000f, -0.154508f}},
    {{-0.500000f, -0.500000f,  0.000000f, 1.0f}, {-0.500000f,  0.000000f,  0.000000f}},
    {{-0.500000f,  0.500000f,  0.000000f, 1.0f}, {-0.500000f,  0.000000f,  0.000000f}},
    {{-0.475528f, -0.500000f,  0.154508f, 1.0f}, {-0.475528f,  0.000000f,  0.154508f}},
    {{-0.475528f,  0.500000f,  0.154508f, 1.0f}, {-0.475528f,  0.000000f,  0.154508f}},
    {{-0.404508f, -0.500000f,  0.293893f, 1.0f}, {-0.404508f,  0.000000f,  0.293893f}},
    {{-0.404508f,  0.500000f,  0.293893f, 1.0f}, {-0.404508f,  0.000000f,  0.293893f}},
    {{-0.293893f, -0.500000f,  0.404508f, 1.0f}, {-0.293893f,  0.000000f,  0.404508f}},
    {{-0.293893f,  0.500000f,  0.404508f, 1.0f}, {-0.293893f,  0.000000f,  0.404508f}},
    {{-0.154508f, -0.500000f,  0.475528f, 1.0f}, {-0.154508f,  0.000000f,  0.475528f}},
    {{-0.154508f,  0.500000f,  0.475528f, 1.0f}, {-0.154508f,  0.000000f,  0.475528f}},
    {{-0.000000f, -0.500000f,  0.500000f, 1.0f}, {-0.000000f,  0.000000f,  0.500000f}},
    {{-0.000000f,  0.500000f,  0.500000f, 1.0f}, {-0.000000f,  0.000000f,  0.500000f}},
    {{ 0.154508f, -0.500000f,  0.475528f, 1.0f}, { 0.154508f,  0.000000f,  0.475528f}},
    {{ 0.154508f,  0.500000f,  0.475528f, 1.0f}, { 0.154508f,  0.000000f,  0.475528f}},
    {{ 0.293893f, -0.500000f,  0.404508f, 1.0f}, { 0.293893f,  0.000000f,  0.404508f}},
    {{ 0.293893f,  0.500000f,  0.404508f, 1.0f}, { 0.293893f,  0.000000f,  0.404508f}},
    {{ 0.404508f, -0.500000f,  0.293893f, 1.0f}, { 0.404508f,  0.000000f,  0.293893f}},
    {{ 0.404508f,  0.500000f,  0.293893f, 1.0f}, { 0.404508f,  0.000000f,  0.293893f}},
    {{ 0.475528f, -0.500000f,  0.154508f, 1.0f}, { 0.475528f,  0.000000f,  0.154508f}},
    {{ 0.475528f,  0.500000f,  0.154508f, 1.0f}, { 0.475528f,  0.000000f,  0.154508f}}
};
static const int cylinderNumVertices = 40;

static const GLint cylinderIndices[] = {
    0, 3, 1, 0, 2, 3, 
    2, 5, 3, 2, 4, 5, 
    4, 7, 5, 4, 6, 7, 
    6, 9, 7, 6, 8, 9, 
    8, 11, 9, 8, 10, 11, 
    10, 13, 11, 10, 12, 13, 
    12, 15, 13, 12, 14, 15, 
    14, 17, 15, 14, 16, 17, 
    16, 19, 17, 16, 18, 19, 
    18, 21, 19, 18, 20, 21, 
    20, 23, 21, 20, 22, 23, 
    22, 25, 23, 22, 24, 25, 
    24, 27, 25, 24, 26, 27, 
    26, 29, 27, 26, 28, 29, 
    28, 31, 29, 28, 30, 31, 
    30, 33, 31, 30, 32, 33, 
    32, 35, 33, 32, 34, 35, 
    34, 37, 35, 34, 36, 37, 
    36, 39, 37, 36, 38, 39, 
    38, 1, 39, 38, 0, 1
};
static const int cylinderNumIndices = 120;

class Cylinder : public Entity {
public:
    Cylinder(byte materialId) {
        if(m_cylinderMeshId == 0xFF) {
            Mesh *cylinderMesh = new Mesh(std::vector<Vertex>(cylinderVertices, cylinderVertices + cylinderNumVertices), std::vector<GLint>(cylinderIndices, cylinderIndices + cylinderNumIndices));
            m_cylinderMeshId = cylinderMesh->getId();

            MeshRegistry *registry = MeshRegistry::getRegistry();
            registry->registerMesh(cylinderMesh);
        }

        MeshRegistry *registry = MeshRegistry::getRegistry();
        MeshRef mesh = registry->getMesh(m_cylinderMeshId);
        std::vector<glm::vec2> texCoords;
        for(std::vector<Vertex>::const_iterator currVertex = mesh->getVertices().begin(); currVertex != mesh->getVertices().end(); currVertex++) {
            texCoords.push_back(glm::vec2(glm::atan(currVertex->position.x / currVertex->position.z) / (2 * glm::pi<float>()), currVertex->position.y + 0.5f));
        }
        p_textureCoords = texCoords;

        p_meshId = m_cylinderMeshId;
        p_materialId = materialId;
    }

    ~Cylinder() {}

private:
    static byte m_cylinderMeshId;
};

// Initalize to sentinal 255 as it's greater than the max number of meshes (128)
byte Cylinder::m_cylinderMeshId = 0xFF;

#endif