
#include <fstream>

#include "header.hpp"



void saveToFile(const std::string& filename, const Groups& groups) {
    std::ofstream outFile(filename);

    if (!outFile.is_open()) {
        return;
    }
    for (const auto& group : groups) {
        const std::string& groupName = group.first;
        const std::vector<Student>& students = group.second;

        outFile << "Group: " << groupName << "\n";


        for (const Student& student : students) {
            outFile << "  Student: " << student.Name << ", Year: " << student.Year << "\n";


            for (const auto& subjectScore : student.RecordBook) {
                const std::string& subject = subjectScore.first;
                Score score = subjectScore.second;

                outFile << "    " << subject << ": " << static_cast<int>(score) << "\n";
            }
        }


        outFile << std::endl;
    }

    outFile.close();
}

void loadFromFile(const std::string& filename, Groups& outGroups) {
    std::ifstream inFile(filename);
    if (!inFile.is_open()) {
        return;
    }

    std::string line;
    std::string currentGroup;


    while (std::getline(inFile, line)) {
        if (line.empty()) {
            continue;
        }

        if (line.rfind("Group: ", 0) == 0) {
            currentGroup = line.substr(7);
            outGroups[currentGroup];
            continue;
        }

        if (line.rfind("  Student: ", 0) == 0) {
            size_t pos = line.find(", Year: ");
            if (pos == std::string::npos) {
                continue;
            }

            std::string name = line.substr(11, pos - 11);
            int year = std::stoi(line.substr(pos + 8));

            Student student;
            student.Name = name;
            student.Year = year;

            outGroups[currentGroup].push_back(student);
            continue;
        }


        if (line.rfind("    ", 0) == 0 && line.find(": ") != std::string::npos) {
            if (currentGroup.empty() || outGroups[currentGroup].empty()) {
                continue;
            }

            size_t colonPos = line.find(": ");
            std::string subject = line.substr(4, colonPos - 4);
            int score = std::stoi(line.substr(colonPos + 2));



            outGroups[currentGroup].back().RecordBook[subject] = static_cast<Score>(score);
        }
    }

    inFile.close();
}