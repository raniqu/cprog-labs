//25 вариант

#include <iostream>
#include <fstream>
#include <deque>
#include <list>
#include <algorithm>
#include <string>
#include <sstream>


class BankCredit {
private:
    std::string name;
    double amount;
    std::string currency;
    double rate;

public:
    BankCredit() : amount(0.0), rate(0.0) {}
    BankCredit(const std::string& n, double a, const std::string& c, double r)
        : name(n), amount(a), currency(c), rate(r) {}

    double getRate() const { return rate; }

    friend std::ostream& operator<<(std::ostream& os, const BankCredit& bc) {
        os << bc.name << " | " << bc.amount << " " << bc.currency << " | " << bc.rate << "%";
        return os;
    }

    bool operator<(const BankCredit& other) const {
        return rate < other.rate;
    }
};

bool readFromFile(const std::string& filename, std::deque<BankCredit>& credits) {
    std::ifstream infile(filename);
    if (!infile.is_open()) return false;
    std::string line;
    while (std::getline(infile, line)) {
        if (line.empty()) continue;
        std::istringstream iss(line);
        std::string name, currency;
        double amount, rate;
        if (iss >> name >> amount >> currency >> rate)
            credits.emplace_back(name, amount, currency, rate);
    }
    return true;
}

template<typename Container>
void print(std::ostream& os, const Container& cont, const std::string& title) {
    os << title << ":\n";
    for (const auto& item : cont) os << "  " << item << "\n";
    os << "\n";
}

int main() {
    std::deque<BankCredit> source;
    if (!readFromFile("input.txt", source)) {
        std::cerr << "Error: cannot open input.txt\n";
        return 1;
    }

    std::ofstream out("output.txt");
    if (!out) {
        std::cerr << "Error: cannot create output.txt\n";
        return 1;
    }

    print(out, source, "Original deque (bank credits)");

    std::sort(source.begin(), source.end());
    print(out, source, "Sorted deque (by interest rate)");

    std::list<BankCredit> target;
    std::copy(source.begin(), source.end(), std::back_inserter(target));
    print(out, target, "Copied list (from sorted deque)");

    out.close();

    std::cout << "Done. Results written to output.txt\n";
    return 0;
}