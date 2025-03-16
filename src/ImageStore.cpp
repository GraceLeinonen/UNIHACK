#include "ImageStore.hpp"

#include <string>
#include <vector>
#include <unordered_map>
#include <filesystem>

ImageStore::ImageStore() {}

void ImageStore::readImageDirectory(std::string folderPath) {

 // Iterate through the directory
 for (const auto& entry : std::filesystem::directory_iterator(folderPath)) {

    // Check if the entry is a file
    if (std::filesystem::is_regular_file(entry.status())) {

        // Extract the file name
        std::string fileName = entry.path().filename().string();

        // Check if the file matches the target name
        for (auto& i : Habits::getAllHabits()) {

        if (startsWith(fileName, i.getName())) {

            if (habitMap.find(i) == habitMap.end()) {

                std::vector<std::filesystem::path> name;
                habitMap[i] = name;

            }
            habitMap[i].push_back(entry.path());

        }
    }
    }
}
}

std::unordered_map<Habits,std::vector<std::filesystem::path>> ImageStore::getHabitMap() {
    return habitMap;
}

bool ImageStore::startsWith(const std::string& str, const std::string& prefix) {
    // Ensure the prefix length is not greater than the string length
    if (prefix.size() > str.size()) {
        return false;
    }
    return str.compare(0, prefix.size(), prefix) == 0;
}
