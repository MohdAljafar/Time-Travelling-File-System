#ifndef FILE_HPP
#define FILE_HPP

#include <string>
#include <vector>
#include <unordered_map>

#include "TreeNode.hpp"

class File{
public:
    TreeNode* root;
    TreeNode* active_version ;
    std::unordered_map <int , TreeNode*> version_map;
    int total_versions ;

    File(TreeNode* root) : root(root), active_version(root), total_versions(1), version_map({{0, root}}) {}

};


#endif