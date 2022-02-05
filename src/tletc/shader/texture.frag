#version 330

struct TexMaterial {
    sampler2D texSampler;

    float ka;
    float kd;
    float ks;
    float se;
};

flat in uint f_materialId;
in vec4 f_vWorldPos;
in vec3 f_vNorm;
in vec2 f_vTexCoords;

out vec4 o_fragColor;

uniform vec4 u_cameraPos;
uniform TexMaterial u_materials[16];
uniform vec4 u_lightPos;

void main() {
    vec3 normalVec  = normalize(f_vNorm);
    vec3 lightVec   = normalize(vec3(u_lightPos - f_vWorldPos));
    vec3 viewVec    = normalize(vec3(u_cameraPos - f_vWorldPos));
    vec3 reflectVec = normalize(-reflect(lightVec, normalVec));

    vec4 textureColor = texture(u_materials[f_materialId].texSampler, f_vTexCoords);

    vec3 ambientColor  = vec3(textureColor) * u_materials[f_materialId].ka;
    vec3 diffuseColor  = vec3(textureColor) * u_materials[f_materialId].kd * max(dot(normalVec, lightVec), 0);
    vec3 specularColor = vec3(textureColor) * u_materials[f_materialId].ks * pow(max(dot(viewVec, reflectVec), 0), u_materials[f_materialId].se);

    o_fragColor = vec4(ambientColor + diffuseColor + specularColor, textureColor.a);
}