#include <iostream>
#include <string>
using namespace std;

class School {
protected:
    string name;
    int students;
public:
    School(const string& n, int s) : name(n), students(s) {}
    virtual void print() const {
        cout << "School: " << name << ", students: " << students << endl;
    }
};

class SpecializedSchool : public School {
    string specialization;
public:
    SpecializedSchool(const string& n, int s, const string& spec)
        : School(n, s), specialization(spec) {}
    void print() const override {
        School::print();
        cout << "Specialization: " << specialization << endl;
    }
};

int main() {
    School school("Gymnasium No. 5", 620);
    SpecializedSchool spec("School of Arts", 340, "music");

    cout << "Static polymorphism\n" << endl;
    school.print();
    spec.print();

    cout << "Dynamic polymorphism" << endl;
    School* ptr = &spec;
    ptr->print();

    return 0;
}