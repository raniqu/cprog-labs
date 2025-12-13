#include "lab.hpp"

int main() {
    std::vector<int> v{5, 8, 9, 1, -10, 23};
    //1
    std::vector<int>::iterator it = Find(v.begin(), v.end(), 1);
    //2
    std::vector<int> data = {1, 2, 3, 4, 5};
    std::vector<int>::iterator it_new = findInSorted(data.begin(), data.end(), 2);
    //3
    int words = wordsCounter("can you can");
    //4
    std::map<std::string, int> words = wordsMapCounter("can you can");
    //5
    std::vector<std::string> unique = uniqueWords("Can you can");
    //6
    int words_new = diffWordsCounter("can you can a can");
    //7
    std::list<int> nums = {1, 5, 4, -3};
    reverseNum(nums);
    //8
    plusesDeleter(v);
    //9
    Sort(nums);
}