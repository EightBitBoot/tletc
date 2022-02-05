
#include "mesh.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>

byte Mesh::s_nextId = 0;

Mesh::Mesh(const std::vector<Vertex> &vertices, const std::vector<GLint> &indices) :
    p_vertices(vertices),
    p_indices(indices),
    m_meshId(s_nextId++) // Increment s_nextId for the next constructor
{}

Mesh::~Mesh() {}

byte Mesh::getId() const { return m_meshId; }

const std::vector<Vertex> &Mesh::getVertices() const { return p_vertices; }
const std::vector<GLint>  &Mesh::getIndices() const { return p_indices; }