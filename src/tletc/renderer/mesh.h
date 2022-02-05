#ifndef __MESH_H__
#define __MESH_H__

#include <vector>
#include <array>
#include <memory>

#include <GL/glew.h>

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

#include <tletc/types.h>

class Mesh {
public:
    Mesh(const std::vector<Vertex> &vertices, const std::vector<GLint> &indices);
    ~Mesh();

    byte getId() const;
    const std::vector<Vertex> &getVertices() const;
    const std::vector<int>    &getIndices() const;

protected:
    std::vector<Vertex> p_vertices;
    std::vector<int> p_indices;

private:
    byte m_meshId; 

    static byte s_nextId;
};

using MeshRef = std::shared_ptr<Mesh>;

#endif