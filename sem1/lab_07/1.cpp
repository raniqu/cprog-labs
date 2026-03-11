#include <fstream>
#include <iostream>
#include "header.hpp"

void saveToFile(const std::string& filename, const std::vector<std::string>& data) {
    std::ofstream outFile(filename);

    if (outFile.is_open()){
        for (const std::string& elem : data) {
            outFile << elem << std::endl;
        }
        outFile.close();
    }
}


void loadFromFile(const std::string& filename, std::vector<std::string>& outData) {
    std::ifstream inFile(filename);

    if (inFile.is_open()) {
        std::string word;
        while (inFile >> word) {
            outData.push_back(word);
        }
        inFile.close();
    }
}