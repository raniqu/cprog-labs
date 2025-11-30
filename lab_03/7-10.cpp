#include <algorithm>
#include <iostream>
#include <regex>
#include <string>
//task7
void longest_shortest(const std::string& name_one, const std::string& name_two, const std::string& name_three, std::string& the_longest, std::string& the_shortest) {
    the_longest = name_one;
    the_shortest = name_one;

    if (name_two.length() > the_longest.length()) {
        the_longest = name_two;
    }
    if (name_three.length() > the_longest.length()) {
        the_longest = name_three;
    }

    if (name_two.length() < the_shortest.length()) {
        the_shortest = name_two;
    }
    if (name_three.length() < the_shortest.length()) {
        the_shortest = name_three;
    }
}
//task8
std::string sub_str(const std::string& word, int m, int n) {
    if ((m>n) || (m < 0) || (n >= word.length())) {
        throw std::out_of_range("incorrect indexes");
    }
    return word.substr(m, n-m+1);
}

//task9
void add_stars(std::string& word) {
    int n = word.length();
    std::string stars(n, '*');
    word = stars + word + stars;
}

//task10
int percent_of_a(const std::string& word) {
     int n = std::count(word.begin(), word.end(), 'a');
    return (n*100) /word.size();
}

//task11
std::string replace_can(const std::string& new_word) {
    std::string data = "Can you can a can as a canner can can a can?";
    std::regex pattern(R"(\bcan\b)", std::regex::icase);
    return std::regex_replace(data, pattern, new_word);
}
