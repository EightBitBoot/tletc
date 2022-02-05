#ifndef __TYPES_H__
#define __TYPES_H__

#include <memory>

#include <glm/vec4.hpp>
#include <glm/vec3.hpp>

typedef struct Vertex_s {
    glm::vec4 position;
    glm::vec3 normal;
} Vertex;

typedef unsigned char byte;

#endif