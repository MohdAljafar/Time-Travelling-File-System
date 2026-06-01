#ifndef FILE_SYSTEM_HPP
#define FILE_SYSTEM_HPP

#include <string>
#include <vector>
#include <unordered_map>

#include "File.hpp"


class FileSystem {
private:
    std::unordered_map<std::string, File*> files;   //filename -> filePointer

public:
    void createFile(const std::string& filename);
    File* getFile(const std::string& filename);
    std::string readFile(const std::string& filename);
    void insertContent(const std::string& filename, const std::string& content);
    void updateContent(const std::string& filename, const std::string& content);
    void createSnapshot(const std::string& filename, const std::string& message);
    void rollbackToVersion(const std::string& filename, int version_id);
    void history(const std::string& filename);

    void recentFiles(int k);
    void biggestTrees(int k);
   
};


#endif