#include "../include/FileSystem.hpp"
#include "../include/File.hpp"
#include "../include/TreeNode.hpp"

#include <string>
#include <iostream>
#include <algorithm>
#include <ctime>
#include <queue>

void FileSystem::createFile(const std::string &filename){
    if(!files.count(filename)){
        
        TreeNode* rootVersion = new TreeNode();

        auto newFile = new File(rootVersion);

        files[filename] = newFile;
    }
}

File* FileSystem::getFile(const std::string& filename){
    if(files.count(filename)){
        return files[filename];
    }
    return nullptr;
}

std::string FileSystem::readFile(const std::string& filename){
    File* file = getFile(filename);
    if(file){
        std::string content = file->active_version->content;
        if(content.empty()){
            return "(Empty File)";
        }
        return content;
    }
    return "File not found";
}

void FileSystem::insertContent(const std::string& filename, const std::string& content){
    File* file = getFile(filename);
    if(file){
        if(file->active_version->snapshot_timestamp != 0){
            // If the active version is a snapshot, create a new version
            TreeNode* newVersion = new TreeNode(file->total_versions, content);
            newVersion->parent = file->active_version;
            file->active_version->children.push_back(newVersion);
            file->active_version = newVersion;
            file->version_map[file->total_versions] = newVersion;
            file->total_versions++;
        } else {
            // If the active version is not a snapshot, directly update the content
            file->active_version->content = file->active_version->content + content;
            file->active_version->last_modified_timestamp = time(nullptr);
        }
    }else{
        std::cout << "File not found" << std::endl;
    }
}

void FileSystem::updateContent(const std::string& filename, const std::string& content){
    File* file = getFile(filename);
    if(file){
        if(file->active_version->snapshot_timestamp != 0){
            // If the active version is a snapshot, create a new version
            TreeNode* newVersion = new TreeNode(file->total_versions, content);
            newVersion->parent = file->active_version;
            file->active_version->children.push_back(newVersion);
            file->active_version = newVersion;
            file->version_map[file->total_versions] = newVersion;
            file->total_versions++;
        } else {
            // If the active version is not a snapshot, directly update the content
            file->active_version->content = content;
            file->active_version->last_modified_timestamp = time(nullptr);
        }
    }else{
        std::cout << "File not found" << std::endl;
    }
}

void FileSystem::createSnapshot(const std::string& filename, const std::string& message){
    File* file = getFile(filename);
    if(file){
        file->active_version->message = message;
        file->active_version->snapshot_timestamp = time(nullptr);
    }else{
        std::cout << "File not found" << std::endl;
    }
}

void FileSystem::rollbackToVersion(const std::string& filename, int version_id){
    File* file = getFile(filename);
    if(file){
        if(version_id == -1){
            file->active_version = file->active_version->parent ? file->active_version->parent : file->active_version;
        } 
        else if(file->version_map.count(version_id)){
            file->active_version = file->version_map[version_id];
        } 
        else {
            std::cout << "Version not found" << std::endl;
        }
    }else{
        std::cout << "File not found" << std::endl;
    }
}

void FileSystem::history(const std::string& filename){
    File* file = getFile(filename);
    if(!file){
        std::cout << "File not found" << std::endl;
        return;
    }
    
    // Traverse from active_version to root, collecting all nodes
    std::vector<TreeNode*> path;
    TreeNode* current = file->active_version;
    
    while(current != nullptr){
        path.push_back(current);
        current = current->parent;
    }
    
    // Reverse to display chronologically (root to active)
    std::reverse(path.begin(), path.end());
    
    // Display all snapshotted versions on the path
    std::cout << "History of file: " << filename << std::endl;
    std::cout << "======================================" << std::endl;
    
    for(TreeNode* node : path){
        // Only display snapshots (nodes with snapshot_timestamp != 0)
        if(node->snapshot_timestamp != 0){
            std::cout << "VersionID: " << node->version_id << " | ";
            
            // Convert timestamp to readable format
            char buffer[80];
            struct tm* timeinfo = localtime(&node->snapshot_timestamp);
            strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeinfo);
            
            std::cout << "Timestamp: " << buffer << " | ";
            std::cout << "Message: " << node->message << std::endl;
            std::cout << "--------------------------------------" << std::endl;
        }
    }
    
    std::cout << "======================================" << std::endl;
}

void FileSystem::recentFiles(int k){
    
    std::vector<std::string> recentFilesList;
    std::priority_queue<std::pair<time_t, std::string>,
                        std::vector<std::pair<time_t, std::string>>, 
                        std::greater<std::pair<time_t, std::string>>
                        > pq; // Min-heap to store timestamps and corresponding filenames

    for(const auto& entry : files){
        const std::string& filename = entry.first;
        File* file = entry.second;
        time_t lastModified = file->active_version->last_modified_timestamp;
        pq.push({lastModified, filename});
        if(pq.size() > k){
            pq.pop(); // Remove the least recent file if we have more than k
        }
    }
    
    while(!pq.empty()){
        recentFilesList.push_back(pq.top().second);
        pq.pop();
    }

    reverse(recentFilesList.begin(), recentFilesList.end()); // Reverse to get most recent first
    
    
    // Display the top k recent files
    std::cout << "Top " << k << " Recent Files:" << std::endl;
    std::cout << "======================================" << std::endl;
    
    for(const std::string& filename : recentFilesList){
        std::cout << filename << std::endl;
    }
    std::cout << "======================================" << std::endl;
}

void FileSystem::biggestTrees(int k){
    std::vector<std::pair<std::string, int>> biggestTreesFiles; // Vector to store tree sizes and corresponding filenames

    std::priority_queue<std::pair<time_t, std::string>,
                        std::vector<std::pair<time_t, std::string>>, 
                        std::greater<std::pair<time_t, std::string>>
                        > pq; // Min-heap to store timestamps and corresponding filenames

    for(const auto& entry : files){
        const std::string& filename = entry.first;
        File* file = entry.second;
        
        pq.push({file->total_versions, filename});
        if(pq.size() > k){
            pq.pop(); // Remove the smallest tree if we have more than k
        }
    }
    
    while(!pq.empty()){
        biggestTreesFiles.push_back({pq.top().second, pq.top().first});
        pq.pop();
    }
    
    reverse(biggestTreesFiles.begin(), biggestTreesFiles.end()); // Reverse to get biggest first

    // Display the top k biggest trees
    std::cout << "Top " << k << " Biggest Trees:" << std::endl;
    std::cout << "======================================" << std::endl;
    
    for(std::pair<std::string, int>& fileInfo : biggestTreesFiles){
        std::cout << "Filename: " << fileInfo.first << "(" << fileInfo.second<<" versions)" << std::endl;
    }
    
    std::cout << "======================================" << std::endl;
}



