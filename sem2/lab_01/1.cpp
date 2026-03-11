#include <iostream>
#include <cstring>
#include <algorithm>

class String {
public:
    ~String();

    String();

    String(const String &rhs);

    String(String&& rhs) noexcept;

    String(const char *data);

    String &operator=(const String &rhs);

    String &operator+=(const String &rhs);

    String &operator*=(unsigned int m);

    bool operator==(const String &rhs) const;

    bool operator<(const String &rhs) const;

    size_t Find(const String &substr) const;

    void Replace(char oldSymbol, char newSymbol);

    size_t Size() const;

    bool Empty() const;

    char operator[](size_t index) const;

    char &operator[](size_t index);

    void RTrim(char symbol);

    void LTrim(char symbol);

    void swap(String &oth);

    friend std::ostream &operator<<(std::ostream &, const String &);

private:
    char *Data;
};

// реализация методов класса

String::~String() {
    delete[] Data;
    Data = nullptr;
}

String::String() : Data(nullptr) {
    Data = new char[1];
    Data[0] = '\0';
}

String::String(const String &rhs) : Data(nullptr) {
    if (rhs.Data) {
        size_t len = std::strlen(rhs.Data);
        Data = new char[len + 1];
        std::strcpy(Data, rhs.Data);
    } else {
        Data = new char[1];
        Data[0] = '\0';
    }
}

String::String(String&& rhs) noexcept : Data(rhs.Data) {
    rhs.Data = nullptr;
}

String::String(const char *data) : Data(nullptr) {
    if (data) {
        size_t len = std::strlen(data);
        Data = new char[len + 1];
        std::strcpy(Data, data);
    } else {
        Data = new char[1];
        Data[0] = '\0';
    }
}

String &String::operator=(const String &rhs) {
    if (this != &rhs) {
        String temp(rhs);
        swap(temp);
    }
    return *this;
}

String &String::operator+=(const String &rhs) {
    if (rhs.Empty()) {
        return *this;
    }

    size_t len1 = Size();
    size_t len2 = rhs.Size();

    char *newData = new char[len1 + len2 + 1];
    if (Data) {
        std::strcpy(newData, Data);
    } else {
        newData[0] = '\0';
    }
    std::strcat(newData, rhs.Data);

    delete[] Data;
    Data = newData;

    return *this;
}

String &String::operator*=(unsigned int m) {
    if (m == 0 || Empty()) {
        delete[] Data;
        Data = new char[1];
        Data[0] = '\0';
        return *this;
    }

    if (m == 1) {
        return *this;
    }

    size_t len = Size();
    char *newData = new char[len * m + 1];
    newData[0] = '\0';

    for (unsigned int i = 0; i < m; ++i) {
        std::strcat(newData, Data);
    }

    delete[] Data;
    Data = newData;

    return *this;
}

bool String::operator==(const String &rhs) const {
    if (Data == rhs.Data) return true;
    if (!Data || !rhs.Data) return false;
    return std::strcmp(Data, rhs.Data) == 0;
}

bool String::operator<(const String &rhs) const {
    if (!Data && !rhs.Data) return false;
    if (!Data) return true;
    if (!rhs.Data) return false;
    return std::strcmp(Data, rhs.Data) < 0;
}

size_t String::Find(const String &substr) const {
    if (substr.Empty()) {
        return 0;
    }
    if (Empty()) {
        return static_cast<size_t>(-1);
    }

    const char *pos = std::strstr(Data, substr.Data);
    if (pos) {
        return static_cast<size_t>(pos - Data);
    }
    return static_cast<size_t>(-1);
}

void String::Replace(char oldSymbol, char newSymbol) {
    if (!Data) return;
    for (size_t i = 0; Data[i] != '\0'; ++i) {
        if (Data[i] == oldSymbol) {
            Data[i] = newSymbol;
        }
    }
}

size_t String::Size() const {
    if (!Data) return 0;
    return std::strlen(Data);
}

bool String::Empty() const {
    return !Data || Data[0] == '\0';
}

char String::operator[](size_t index) const {
    return Data[index];
}

char &String::operator[](size_t index) {
    return Data[index];
}

void String::RTrim(char symbol) {
    if (!Data || Empty()) return;

    size_t len = Size();
    while (len > 0 && Data[len - 1] == symbol) {
        --len;
    }
    Data[len] = '\0';
}

void String::LTrim(char symbol) {
    if (!Data || Empty()) return;

    size_t start = 0;
    while (Data[start] == symbol) {
        ++start;
    }

    if (start > 0) {
        std::memmove(Data, Data + start, Size() - start + 1);
    }
}

void String::swap(String &oth) {
    std::swap(Data, oth.Data);
}

std::ostream &operator<<(std::ostream &out, const String &str) {
    if (str.Data) {
        out << str.Data;
    }
    return out;
}

// реализация функций

String operator+(const String &a, const String &b) {
    String result = a;
    result += b;
    return result;
}

String operator*(const String &a, unsigned int b) {
    String result = a;
    result *= b;
    return result;
}

bool operator!=(const String &a, const String &b) {
    return !(a == b);
}

bool operator>(const String &a, const String &b) {
    return b < a;
}




int main() {


    String s1;
    std::cout << "1. Default constructor: s1 = \"" << s1 << "\" (Empty: " << s1.Empty() << ")\n";

    String s2("Hello");
    std::cout << "2. Constructor from char*: s2 = \"" << s2 << "\"\n";

    String s3(s2);
    std::cout << "3. Copy constructor: s3 = \"" << s3 << "\"\n";

    String s31 = String("Moved!");
    std::cout << "3.1 Move constructor: s31 = \"" << s31 << "\"\n";

    std::cout << "4. s2.Size() = " << s2.Size() << ", s2.Empty() = " << s2.Empty() << "\n";
    std::cout << "   s1.Size() = " << s1.Size() << ", s1.Empty() = " << s1.Empty() << "\n";

    std::cout << "5. s2[0] = '" << s2[0] << "', s2[4] = '" << s2[4] << "'\n";
    s2[0] = 'h';
    std::cout << "   After s2[0] = 'h': s2 = \"" << s2 << "\"\n";

    String s4("Hello");
    std::cout << "6. s2 == s4: " << (s2 == s4) << ", s2 != s4: " << (s2 != s4) << "\n";

    String s5("World");
    std::cout << "7. s2 < s5: " << (s2 < s5) << ", s2 > s5: " << (s2 > s5) << "\n";

    String s6("Hello");
    s6 += String(" ");
    s6 += String("World");
    std::cout << "8. After += : s6 = \"" << s6 << "\"\n";

    String s7 = String("forever") + String("young");
    std::cout << "9. operator+: s7 = \"" << s7 << "\"\n";

    String s8("ab");
    s8 *= 3;
    std::cout << "10. operator*=: s8 = \"" << s8 << "\"\n";

    String s9 = String("x") * 5;
    std::cout << "11. operator*: s9 = \"" << s9 << "\"\n";

    String s10("Hello World");
    std::cout << "12. Find 'World' in \"" << s10 << "\": " << s10.Find(String("World")) << "\n";
    std::cout << "    Find 'xyz' in \"" << s10 << "\": " << s10.Find(String("xyz")) << " (npos)\n";

    String s11("hello world");
    s11.Replace('l', 'L');
    std::cout << "13. After Replace('l', 'L'): s11 = \"" << s11 << "\"\n";

    String s12("___some string___");
    std::cout << "14. Before trim: s12 = \"" << s12 << "\"\n";
    s12.RTrim('_');
    std::cout << "    After RTrim('_'): s12 = \"" << s12 << "\"\n";

    String s13("___some string___");
    s13.LTrim('_');
    std::cout << "    After LTrim('_'): s13 = \"" << s13 << "\"\n";

    String s14("First");
    String s15("Second");
    std::cout << "15. Before swap: s14 = \"" << s14 << "\", s15 = \"" << s15 << "\"\n";
    s14.swap(s15);
    std::cout << "    After swap: s14 = \"" << s14 << "\", s15 = \"" << s15 << "\"\n";

    String s16;
    s16 = String("Assigned");
    std::cout << "16. After assignment: s16 = \"" << s16 << "\"\n";

    s16 = s16;
    std::cout << "17. After self-assignment: s16 = \"" << s16 << "\"\n";

    String s17("Test");
    s17 *= 2;
    s17 += String("!");
    s17.Replace('T', 't');
    std::cout << "18. Combined ops: \"" << s17 << "\"\n";

    size_t pos = s17.Find(String("test"));
    std::cout << "19. Find 'test' in \"" << s17 << "\": " << pos << "\n";

    return 0;
}
