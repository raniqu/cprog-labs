#include <algorithm>
#include <numeric>

#include "include/header.hpp"
//1
void SortByName(std::vector<Student>& data) {

    std::sort(data.begin(), data.end(), [](const Student& a, const Student& b) {
        return a.Name < b.Name;
    });
}
//2
void SortByRating(std::vector<Student>& data) {
    std::sort(data.begin(), data.end(), [](const Student& a, const Student& b) {
        double srA = std::accumulate(a.Ratings.begin(), a.Ratings.end(), 0.0) / a.Ratings.size();
        double srB = std::accumulate(b.Ratings.begin(), b.Ratings.end(), 0.0) / b.Ratings.size();
        return srA < srB;
    });
}
//3
size_t CountTwoness(const std::vector<Student>& data) {
    size_t counter = 0;
    for (const auto& student : data) {
        for (unsigned elem : student.Ratings) {
            if (elem == 2) {
                ++counter;
                break;
            }
        }
    }
    return counter;
}

//4
size_t CountExcellent(const std::vector<Student>& data) {
    size_t counter = data.size();
    for (const auto& student : data) {
        if (student.Ratings.empty()) {
            --counter;
        }
        else {
            for (unsigned elem : student.Ratings) {
                if (elem != 5) {
                    --counter;
                    break;
                }
            }
        }
    }
    return counter;
}

//5
std::vector<Student> VectorMathExcellent(const std::vector<Student>& data) {
    std::vector<Student> result;
    for (const auto& student : data) {
        if (student.Ratings.size() == student.Subjects.size()) {
            for (size_t i = 0; i < student.Subjects.size(); ++i) {
                if (student.Subjects[i] == "Math") {
                    if (student.Ratings[i] == 5) {
                        result.push_back(student);
                        break;
                    }
                }
            }
        }
    }
    return result;
}
//6
std::vector<std::string> GroupsId(const std::vector<Student>& data) {
    std::vector<std::string> result;

    for (const auto& student : data) {
        if (std::find(result.begin(), result.end(), student.GroupId) == result.end()) {
            result.push_back(student.GroupId);
        }
    }
    return result;
}

//7
std::vector<Group> Groups(const std::vector<Student>& data) {
    std::vector<std::string> uniqueGroups = GroupsId(data);
    std::vector<Group> result;

    for (const auto& elem : uniqueGroups) {
        Group newgroup;
        newgroup.Id = elem;
        result.push_back(newgroup);
    }
    for (auto& group : result) {
        for (const auto& student : data) {
            if (student.GroupId == group.Id) {
                group.Students.push_back(student);
            }
        }
    }
    return result;
}