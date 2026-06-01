#include "../include/FileSystem.hpp"

#include <iostream>
#include <algorithm>
#include <queue>
#include <string>
#include <sstream>

int main(){
    FileSystem fs;

    std::string line;
    while(true){
        std::getline(std::cin, line);

        std::stringstream ss(line);
        std::string command;
        ss >> command;
        if(command == "create"){
            std::string filename;
            ss >> filename;
            fs.createFile(filename);
        } 
        else if(command == "read"){
            std::string filename;
            ss >> filename;
            std::cout << fs.readFile(filename) << std::endl;
        } 
        else if(command == "insert"){
            std::string filename, content;
            ss >> filename;
            std::getline(ss, content); // Read the rest of the line as content
            fs.insertContent(filename, content);
        } 
        else if(command == "update"){
            std::string filename, content;
            ss >> filename;
            std::getline(ss, content); // Read the rest of the line as content
            fs.updateContent(filename, content);
        } 
        else if(command == "snapshot"){
            std::string filename, message;
            ss >> filename;
            std::getline(ss, message); // Read the rest of the line as message
            fs.createSnapshot(filename, message);
        } 
        else if(command == "rollback"){
            std::string filename;
            int version_id = -1;
            ss >> filename >> version_id;
            fs.rollbackToVersion(filename, version_id);
        } 
        else if(command == "history"){
            std::string filename;
            ss >> filename;
            fs.history(filename);
        } 
        else if(command == "recent"){
            int k;
            ss >> k;
            fs.recentFiles(k);
        } 
        else if(command == "biggest"){
            int k;
            ss >> k;
            fs.biggestTrees(k);
        } 
        else if(command == "exit"){
            break;
        } 
        else {
            std::cout << "Unknown command" << std::endl;
        }
    }

}

