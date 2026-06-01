#ifndef TREE_NODE_HPP
#define TREE_NODE_HPP

#include <string>
#include <ctime>
#include <vector>

class TreeNode{
public:
    int version_id;
    std::string content; // Empty if it is a root
    std::string message; // Empty if not a snapshot
    time_t created_timestamp ;
    time_t last_modified_timestamp ;
    time_t snapshot_timestamp ; // Null if not a snapshot
    TreeNode* parent;
    std::vector < TreeNode*> children ;


    // Constructor for creating a root version
    TreeNode() : content(""), message("Root Snapshot"), parent(nullptr), version_id(0), children({}) {
        created_timestamp = time(nullptr); //current time
        last_modified_timestamp = created_timestamp;
        snapshot_timestamp = created_timestamp; //root is a snapshot
    }

    // Constructor for creating a new version based on an existing version
    TreeNode(int vId, const std::string &content) : content(content), message(""), parent(nullptr), version_id(vId), children({}) {
        created_timestamp = time(nullptr);
        last_modified_timestamp = created_timestamp;
        snapshot_timestamp = 0; // Not a snapshot
    }
};


#endif