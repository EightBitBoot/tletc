#ifndef __VFS_H__
#define __VFS_H__

#include <string>

namespace tletc {
    // Forward decleration of VFSNode for m_rootNode decleration
    struct VFSNode;

    /// A system for converting virtual paths (semantically a name space only)
    /// to disk paths (the paths passed to the os when doing file i/o)
    ///
    /// This is the answer to the headache of file management when working with a
    /// game engine, including but not limited to avoiding hard coding disk paths
    /// into binaries.  It decouples the virtual file tree from the os file tree,
    /// allowing designers to create any structure they please.
    ///
    /// Physical paths are mounted into the vfs under a virtual path and then can
    /// be addressed by said virtual path.  After the section of the virtual path
    /// that lies in the vfs has been resolved, the rest is copied verbatim to
    /// the resolved path: allowing subdirectories of mounted paths to be accessed
    /// as well.
    ///
    /// Additionally, this system is entirely text based and can be bypassed
    /// completely by passing other strings to file handling functions.
    ///
    /// mountPath() is used to mount a new disk path into the vfs
    /// resolvePath() is used to resolve a virtual path to a path that can be passed
    ///               to a file handing function
    ///
    class VFS {
    // For method documentation see vfs.cpp
    public:
        static VFS *getVFS();
        static void destroyVFS();

        bool mountPath(const std::string &diskPath, const std::string &virtualPath);
        std::string resolvePath(const std::string &virtualPath);

        void dumpTree();
        void clearTree();

    private:
        VFS();
        ~VFS();

        /// The root node of the vfs tree
        VFSNode *m_rootNode;

        /// The singleton instance of VFS
        static VFS* s_vfsInstance;
    };
}

#endif