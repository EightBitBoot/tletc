#version 330

layout(location = 0) in vec4 i_vecPos;
layout(location = 1) in vec3 i_vecNormal;
layout(location = 2) in vec2 i_texCoords; // Unused by phong program
layout(location = 3) in uint i_entityId;
layout(location = 4) in uint i_materialId;

flat out uint f_materialId;
out vec4 f_vWorldPos;
out vec3 f_vNorm;
out vec2 f_vTexCoords;

uniform mat4 u_modelMats[64];
uniform mat4 u_normMats[64];
uniform mat4 u_cameraMat = mat4(1.0f); // Won't always have a camera (at least for testing)
uniform mat4 u_projMat;

uniform vec4 u_lightPos;

void main() {
    f_materialId = i_materialId;
    f_vWorldPos = u_modelMats[i_entityId] * i_vecPos;
    f_vNorm = normalize(mat3(u_normMats[i_entityId]) * i_vecNormal);
    f_vTexCoords = i_texCoords;

    gl_Position = u_projMat * u_cameraMat * f_vWorldPos;
}