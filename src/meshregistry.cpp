
#include "meshregistry.h"

MeshRegistry *MeshRegistry::m_instance = nullptr;

MeshRegistry::MeshRegistry() {

}

MeshRegistry::~MeshRegistry() {

}

MeshRegistry *MeshRegistry::getRegistry() {
    if(m_instance == nullptr) {
        m_instance = new MeshRegistry();
    }

    return m_instance;
}

void MeshRegistry::destroyRegistry() {
    if(m_instance == nullptr) {
        return;
    }

    delete m_instance;
    m_instance = nullptr;
}

bool MeshRegistry::registerMesh(Mesh *mesh) {
    // m_meshes.insert returns std::pair<iterator, bool> where bool is whether the item was inserted sucessfully
    return m_meshes.insert({mesh->getId(), MeshRef(mesh)}).second;
}

bool MeshRegistry::removeMesh(byte meshId) {
    return (bool) m_meshes.erase(meshId);
}

MeshRef MeshRegistry::getMesh(byte meshId) {
    if(m_meshes.find(meshId) == m_meshes.end()) {
        return MeshRef(nullptr);
    }

    return m_meshes.at(meshId);
}