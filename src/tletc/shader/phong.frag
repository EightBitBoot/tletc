#version 330

struct PhongMaterial {
    vec4 ambientColor;
    vec4 diffuseColor;
    vec4 specularColor;

    float ka;
    float kd;
    float ks;
    float se;
};

flat in uint f_materialId;
in vec4 f_vWorldPos;
in vec3 f_vNorm;
in vec2 f_vTexCoords; // Unused but here for compatibility with common vertex shader

out vec4 o_fragColor;

uniform vec4 u_cameraPos;
uniform PhongMaterial u_materials[16];
uniform vec4 u_lightPos;

void main() {
    vec3 normalVec  = normalize(f_vNorm);
    vec3 lightVec   = normalize(vec3(u_lightPos - f_vWorldPos));
    vec3 viewVec    = normalize(vec3(u_cameraPos - f_vWorldPos));
    vec3 reflectVec = normalize(-reflect(lightVec, normalVec));

    vec3 ambientColor  = vec3(u_materials[f_materialId].ambientColor)  * u_materials[f_materialId].ka;
    vec3 diffuseColor  = vec3(u_materials[f_materialId].diffuseColor)  * u_materials[f_materialId].kd * max(dot(normalVec, lightVec), 0);
    vec3 specularColor = vec3(u_materials[f_materialId].specularColor) * u_materials[f_materialId].ks * pow(max(dot(viewVec, reflectVec), 0), u_materials[f_materialId].se);

    o_fragColor = vec4(ambientColor + diffuseColor + specularColor, 1.0f);
}