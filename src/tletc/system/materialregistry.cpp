
#include "materialregistry.h"

MaterialRegistry *MaterialRegistry::m_instance = nullptr;

MaterialRegistry::MaterialRegistry()  {}
MaterialRegistry::~MaterialRegistry() {}

MaterialRegistry *MaterialRegistry::getRegistry() {
    if(m_instance == nullptr) {
        m_instance = new MaterialRegistry();
    }

    return m_instance;
}

void MaterialRegistry::destroyRegistry() {
    if(m_instance == nullptr) {
        delete m_instance;
    }

    m_instance = nullptr;
}

bool MaterialRegistry::registerMaterial(Material *material) {
    return m_materials.insert({material->getId(), MaterialRef(material)}).second;
}

bool MaterialRegistry::removeMaterial(byte materialId) {
    return (bool) m_materials.erase(materialId);
}

MaterialRef MaterialRegistry::getMaterial(byte materialId) {
    if(m_materials.find(materialId) == m_materials.end()) {
        return MaterialRef(nullptr);
    }

    return m_materials.at(materialId);
}