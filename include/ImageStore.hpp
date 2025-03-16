#pragma once

#include <string>
#include <vector>
#include <filesystem>
#include <unordered_map>

#include "Habits.hpp"

class ImageStore {

    private:
    std::string folderPath = "assets/textures"; // Replace with the path to your folder
    std::unordered_map<Habits,std::vector<std::filesystem::path>> habitMap;

    public:
    ImageStore();
    void readImageDirectory(std::string folderPath);
    bool startsWith(const std::string& str, const std::string& prefix);
    std::unordered_map<Habits,std::vector<std::filesystem::path>> getHabitMap();
};