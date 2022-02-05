#ifndef __MATERIAL_REGISTRY_H__
#define __MATERIAL_REGISTRY_H__

#include <unordered_map>

#include <tletc/renderer/material.h>

class MaterialRegistry {
public:
    static MaterialRegistry *getRegistry();
    static void destroyRegistry();

    bool registerMaterial(Material *material);
    bool removeMaterial(byte materialId);

    MaterialRef getMaterial(byte materialId);

private:
    MaterialRegistry();
    ~MaterialRegistry();

    static MaterialRegistry *m_instance;
    std::unordered_map<byte, MaterialRef> m_materials;
};

#endif