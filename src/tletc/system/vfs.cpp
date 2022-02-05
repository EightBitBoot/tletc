
#include "vfs.h"

#include <filesystem>
#include <unordered_map>
#include <string>

#include "../internal_core.h"

namespace tletc {
    /// A single node in the vfs tree
    ///
    struct VFSNode {
        /// The virtual path section that refers to this node
        std::string nodeName;
        /// The disk path this node points to (can be "")
        std::string diskPath;
        /// The node's children, indexed by their names
        std::unordered_map<std::string, VFSNode *> children;
    };

    // An alias for iterating over paths
    using path_iterator = std::filesystem::path::iterator;
    // An alias for iterating over a node's children
    using child_iterator = std::unordered_map<std::string, VFSNode *>::iterator;

    /// The singleton instance of VFS
    VFS *VFS::s_vfsInstance = nullptr;

    /// Get the singleton instance of VFS
    ///
    /// @return a pointer to the singleton instance of VFS
    ///
    VFS *VFS::getVFS() {
        if(s_vfsInstance == nullptr) {
            s_vfsInstance = new VFS();
        }

        return s_vfsInstance;
    }

    /// Destroy the singleton instance of VFS
    ///
    void VFS::destroyVFS() {
        if(s_vfsInstance != nullptr) {
            // Delete the vfs instance
            delete s_vfsInstance;
        }

        s_vfsInstance = nullptr;
    }

    /// Construct a new vfs with an empty root node
    ///
    VFS::VFS() :
        m_rootNode(new VFSNode) 
    {
        // Give the root node the symbolic name "/"
        m_rootNode->nodeName = "/";
    }

    /// Destruct the vfs, clearing the tree first
    ///
    VFS::~VFS() {
        // Destroy the vfs tree
        clearTree();
        delete m_rootNode;

    }

    /// Mount a disk path into the vfs
    ///
    /// This function traverses the vfs tree downward based on the sections of virtualPath.
    /// Every time it finds a node that doesn't contain a child with the current section of
    /// virtualPath, it adds a new node to the tree.  Finally, when it gets to the last
    /// section of virtualPath, it points the last node found (or created) to diskPath.
    ///
    /// This function will fail if any of the following conditions occur:
    /// * diskPath is empty
    /// * virtualPath is empty
    /// * virtualPath is an absolute path
    /// * virtualPath has a file extension at the end
    ///
    /// NOTE: There is no provision to prevent mounting over another mount point: if a
    ///       virtual path already points to a disk path and it is passed to this function
    ///       again with a different disk path, the virtual path will now point to the new
    ///       disk path.
    ///
    /// @param diskPath the real (path on disk) path to mount in the vfs at virtualPath
    /// @param virtualPath the virtual (vfs only) path which will point to diskPath
    ///
    /// @return whether the operation was sucessful
    ///
    bool VFS::mountPath(const std::string &diskPath, const std::string &virtualPath) {
        namespace fs = std::filesystem;

        fs::path parsedVirtualPath = std::filesystem::path(virtualPath);

        // TODO(Adin): Add fail condition logging
        // Prevent empty disk paths
        TLETC_IF_COND_RET_VAL(diskPath.empty(), false);
        // Prevent empty virtual paths
        TLETC_IF_COND_RET_VAL(virtualPath.empty(), false);
        // Prevent absolute virtual paths
        TLETC_IF_COND_RET_VAL(parsedVirtualPath.is_absolute(), false);
        // Prevent paths with file extensions
        TLETC_IF_COND_RET_VAL(parsedVirtualPath.has_extension(), false);

        VFSNode *currentNode = m_rootNode;
        VFSNode *newNode = nullptr;
        fs::path::iterator tempIterator;
        for(path_iterator iter = parsedVirtualPath.begin(); iter != parsedVirtualPath.end(); iter++) {
            if(currentNode->children.find(*iter) == currentNode->children.end()) {
                // Current node doesn't contain a child for the current
                // virtual path section: add a new child

                newNode = new VFSNode();
                newNode->nodeName = *iter;

                tempIterator = iter;
                if(++tempIterator == parsedVirtualPath.end()) {
                    // This is the section name in the virtual path:
                    // make the new node point to the supplied disk
                    // path

                    // TODO(Adin): Add log for if diskPath is being overwritten
                    newNode->diskPath = diskPath;
                }

                currentNode->children.insert({*iter, newNode});
            }

            // Descend into the tree
            currentNode = currentNode->children.find(*iter)->second;
        }

        return true;
    }

    /// Resolve the disk path equivalent of a virtual path
    ///
    /// This function performs a depth first search of the vfs tree using the
    /// sections of virtualPath.  There are two stages to this algorithm:
    /// searching and copying.
    /// 
    /// While searching, the current node's children are queried for the
    /// current section of virtualPath.  If it is found, current node is
    /// updated with the results of the query and the search continues,
    /// if it is not, the result is set to the disk path pointed to by
    /// the current node and the algorithm moves to the copying stage.
    ///
    /// While copying, a directory seperator and the current section of
    /// virtualPath is appended to the result.
    ///
    /// This function will fail (return "") if any of the following conditions occur:
    /// * virtualPath is empty
    /// * virtualPath is an absolute path
    ///
    /// @param virtualPath the virtual path to convert to a disk path
    ///
    /// @return the disk path equivalent of virtual path
    ///
    std::string VFS::resolvePath(const std::string &virtualPath) {
        namespace fs = std::filesystem;

        fs::path parsedVirtualPath(virtualPath);

        // TODO(Adin): Add fail condition logging
        // Prevent empty virtual paths
        TLETC_IF_COND_RET_VAL(parsedVirtualPath.empty(), "");
        // Prevent absolute virtual paths
        TLETC_IF_COND_RET_VAL(parsedVirtualPath.is_absolute(), "");

        VFSNode *currentNode = m_rootNode;
        std::string result = "";
        bool doneSearching = false;
        child_iterator findResult;
        for(path_iterator iter = parsedVirtualPath.begin(); iter != parsedVirtualPath.end(); iter++) {
            if(!doneSearching) {
                findResult = currentNode->children.find(*iter);
                if(findResult == currentNode->children.end()) {
                    // Reached a point in the path which is no longer in the vfs:
                    // use the current node's diskPath and start appending
                    // sections of the virtual path to the result

                    result = currentNode->diskPath;
                    doneSearching = true;
                }
                else {
                    currentNode = findResult->second;
                }
            }

            // The odd logic structure here is because this appending always
            // has to occur, even in the same iteration as finding the end
            // of the virtual part of the path
            if(doneSearching) {
                // The end of the virtual section of path was found:
                // start appending sections of the virtual path to
                // the result

                // TODO(Adin): Make the path seperator os independant
                result += "/" + std::string(*iter);
            }
        }

        return result;
    }

    // Print the contents of a VFSNode
    static void dumpNode(VFSNode *node) {
        if(!node->diskPath.empty()) {
            printf("%s -> \"%s\"", node->nodeName.c_str(), node->diskPath.c_str());
        }
        else {
            printf("%s", node->nodeName.c_str());
        }
    }

    // The recursive implimentation of VFS::dumpTree()
    //
    // This function performs a pre order traversal of the vfs tree
    // and prints the results in a style similar to the unix tree
    // command.
    //
    // @param rootNode the current root node of the subtree
    // @param indentation the indentation to print before printing the current root's data
    //
    static void dumpTreeRec(VFSNode *rootNode, const std::string &indentation) {
        child_iterator tempIterator;
        std::string prefix;
        std::string indentationAddition;
        for(child_iterator iter = rootNode->children.begin(); iter != rootNode->children.end(); iter++) {
            tempIterator = iter;
            if(++tempIterator == rootNode->children.end()) {
                // The current child is the last child in the root node:
                // use end cap strings
                prefix = "'-- ";
                indentationAddition = "    ";
            }
            else {
                prefix = "|-- ";
                indentationAddition = "|   ";
            }

            printf("%s%s", indentation.c_str(), prefix.c_str()); dumpNode(iter->second); printf("\n");
            dumpTreeRec(iter->second, indentation + indentationAddition);
        }
    }

    /// Print the current vfs tree in a style similar to the unix tree command
    ///
    void VFS::dumpTree() {
        // Print the label for the root node
        printf("/\n");
        dumpTreeRec(m_rootNode, "");
    }

    // The recursive implementation of VFS::clearTree()
    //
    // This function performs a post order traversal, deleting the current
    // root node
    //
    // @param rootNode the root node of the current subtree
    //
    static void clearTreeRec(VFSNode *rootNode) {
        for(child_iterator iter = rootNode->children.begin(); iter != rootNode->children.end(); iter++) {
            clearTreeRec(iter->second);
        }

        delete rootNode;
    }

    /// Recursively free all nodes in the vfs tree (not including the root node)
    ///
    void VFS::clearTree() {
        // Iterate over the children of m_rootNode here to avoid deleting the root node
        for(child_iterator iter = m_rootNode->children.begin(); iter != m_rootNode->children.end(); iter++) {
            clearTreeRec(iter->second);
        }
        m_rootNode->children.clear();
    }
}