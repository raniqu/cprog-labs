#include <fstream>
#include <iostream>
#include <sstream>

#include "header.hpp"

void saveToFile(const std::string& filename, const std::vector<Book>& data) {
    std::ofstream outFile(filename);
    if (outFile.is_open()) {
        for (const auto& book : data) {
            outFile << book.Author << " " << book.Title << " " << book.Year << std::endl;
        }
        outFile.close();
    }
}

void loadFromFile(const std::string& filename, std::vector<Book>& outData) {
    std::ifstream inFile(filename);
    if (!inFile.is_open()) {
        return;
    }

    std::string line;
    while (std::getline(inFile, line)) {
        if (line.empty()) {
            continue;
        }

        std::istringstream iss(line);
        Book book;

        if (iss >> book.Author >> book.Title >> book.Year) {
            outData.push_back(book);
        }
    }
    inFile.close();
}