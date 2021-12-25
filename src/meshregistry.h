#ifndef __MESH_REGISTRY__
#define __MESH_REGISTRY__

#include <unordered_map>

#include "mesh.h"
#include "material.h"

class MeshRegistry {
public:

    static MeshRegistry *getRegistry();
    static void destroyRegistry();

    bool registerMesh(Mesh *mesh);
    bool removeMesh(byte meshId);

    MeshRef getMesh(byte meshId);

private:
    MeshRegistry();
    ~MeshRegistry();

    static MeshRegistry *m_instance;
    std::unordered_map<byte, MeshRef> m_meshes;
};

#endif