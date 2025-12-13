
#ifndef LAB_HPP
#define LAB_HPP
#include <list>
#include <map>
#include <string>
#include <vector>

std::vector<int>::iterator Find(std::vector<int>::iterator first, std::vector<int>::iterator last, int el);
std::vector<int>::iterator findInSorted(std::vector<int>::iterator first, std::vector<int>::iterator last, int el);
int wordsCounter(const std::string& str);
std::map<std::string, int> wordsMapCounter(const std::string& str);
std::vector<std::string> uniqueWords(const std::string& str);
int diffWordsCounter(const std::string& str);
void reverseNum(std::list<int>&);
void plusesDeleter(std::vector<int>& v);
void Sort(std::list<int>&);

#endif