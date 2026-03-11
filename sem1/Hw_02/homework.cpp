#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <limits>


template<typename T>
class LinkedList {
private:
    struct Node {
        T data;
        Node* next;
        Node* prev;

        Node(T val) : data(val), next(nullptr), prev(nullptr) {}
    };

    Node* head;
    Node* tail;
    int size;
    int type; // тип связного списка

    // вспомог функции
    bool isCircular() const {
        return type == 3 || type == 4;
    }

    bool isDoublyLinked() const {
        return type == 2 || type == 4;
    }

    void makeCircular() {
        if (isCircular() && head != nullptr) {
            tail->next = head;
            if (isDoublyLinked()) {
                head->prev = tail;
            }
        }
    }

    void breakCircular() {
        if (head != nullptr && tail != nullptr) {
            tail->next = nullptr;
            if (isDoublyLinked()) {
                head->prev = nullptr;
            }
        }
    }

public:
    LinkedList(int t = 1) : head(nullptr), tail(nullptr), size(0), type(t) {
        if (t < 1 || t > 4) {
            throw std::invalid_argument("Invalid list type. Valid values: 1-4");
        }
    }

    ~LinkedList() {
        clear();
    }

    // добавить элемент
    void addElement(T value) {
        Node* newNode = new Node(value);

        if (head == nullptr) {
            head = newNode;
            tail = newNode;

            if (isCircular()) {
                newNode->next = head;
                if (isDoublyLinked()) {
                    newNode->prev = newNode;
                }
            }
        } else {

            if (isCircular()) {
                breakCircular();
            }

            if (isDoublyLinked()) {
                newNode->prev = tail;
                tail->next = newNode;
            } else {
                tail->next = newNode;
            }
            tail = newNode;

            makeCircular();
        }
        size++;
    }

    // выводим
    void printList() const {
        if (head == nullptr) {
            std::cout << "List is empty" << std::endl;
            return;
        }

        if (isCircular()) {
            std::cout << "Circular list (" << (isDoublyLinked() ? "doubly-linked" : "singly-linked") << "):" << std::endl;

            Node* current = head;
            int count = 0;

            do {
                std::cout << count + 1 << ": " << current->data;

                if (isDoublyLinked()) {
                    std::cout << " [prev: ";
                    if (current->prev) std::cout << current->prev->data;
                    else std::cout << "NULL";
                    std::cout << ", next: ";
                    if (current->next) std::cout << current->next->data;
                    else std::cout << "NULL";
                    std::cout << "]";
                }

                current = current->next;
                count++;

                if (current != head) {
                    std::cout << " -> ";
                }


                if (count > size * 2) {
                    std::cout << " ... (circular error)";
                    break;
                }
            } while (current != head);

            std::cout << " -> ..." << std::endl;
        } else {
            std::cout << (isDoublyLinked() ? "Doubly-linked" : "Singly-linked") << " list:" << std::endl;

            Node* current = head;
            int count = 0;

            while (current != nullptr) {
                std::cout << count + 1 << ": " << current->data;

                if (isDoublyLinked()) {
                    std::cout << " [prev: ";
                    if (current->prev) std::cout << current->prev->data;
                    else std::cout << "NULL";
                    std::cout << ", next: ";
                    if (current->next) std::cout << current->next->data;
                    else std::cout << "NULL";
                    std::cout << "]";
                }

                current = current->next;
                count++;

                if (current != nullptr) {
                    std::cout << " -> ";
                }
            }
            std::cout << " -> NULL" << std::endl;
        }
    }

    // найти элемент
    std::vector<int> findElement(T value) const {
        std::vector<int> positions;

        if (head == nullptr) {
            return positions;
        }

        Node* current = head;
        int index = 1;

        if (isCircular()) {
            do {
                if (current->data == value) {
                    positions.push_back(index);
                }
                current = current->next;
                index++;

                if (index > size * 2) break;
            } while (current != head);
        } else {
            while (current != nullptr) {
                if (current->data == value) {
                    positions.push_back(index);
                }
                current = current->next;
                index++;
            }
        }

        return positions;
    }

    // удалить первое
    bool deleteFirstOccurrence(T value) {
        if (head == nullptr) {
            return false;
        }

        if (isCircular()) {
            breakCircular();
        }

        Node* current = head;
        Node* prev = nullptr;

        while (current != nullptr) {
            if (current->data == value) {

                if (prev == nullptr) {

                    head = current->next;
                    if (head != nullptr && isDoublyLinked()) {
                        head->prev = nullptr;
                    }
                } else {

                    prev->next = current->next;
                    if (current->next != nullptr && isDoublyLinked()) {
                        current->next->prev = prev;
                    }
                }


                if (current == tail) {
                    tail = prev;
                }

                delete current;
                size--;

                makeCircular();

                return true;
            }

            prev = current;
            current = current->next;
        }

        makeCircular();

        return false;
    }

    // удаляем все
    int deleteAllOccurrences(T value) {
        if (head == nullptr) {
            return 0;
        }

        int count = 0;


        if (isCircular()) {
            breakCircular();
        }

        Node* current = head;
        Node* prev = nullptr;

        while (current != nullptr) {
            if (current->data == value) {
                Node* toDelete = current;

                if (prev == nullptr) {

                    head = current->next;
                    if (head != nullptr && isDoublyLinked()) {
                        head->prev = nullptr;
                    }
                    current = head;
                } else {

                    prev->next = current->next;
                    if (current->next != nullptr && isDoublyLinked()) {
                        current->next->prev = prev;
                    }
                    current = current->next;
                }

                if (toDelete == tail) {
                    tail = prev;
                }

                delete toDelete;
                size--;
                count++;
            } else {
                prev = current;
                current = current->next;
            }
        }

        makeCircular();

        return count;
    }

    // очищаем
    void clear() {
        if (head == nullptr) {
            return;
        }

        if (isCircular()) {
            breakCircular();
        }

        Node* current = head;
        while (current != nullptr) {
            Node* next = current->next;
            delete current;
            current = next;
        }

        head = nullptr;
        tail = nullptr;
        size = 0;
    }

    // сохранить в файл
    void saveToFile(const std::string& filename) const {
        std::ofstream file(filename);
        if (!file.is_open()) {
            throw std::runtime_error("Failed to open file for writing");
        }


        switch (type) {
            case 1: file << ">" << std::endl; break;
            case 2: file << "<>" << std::endl; break;
            case 3: file << ">0" << std::endl; break;
            case 4: file << "<>0" << std::endl; break;
        }


        if (isCircular() && head != nullptr) {
            Node* current = head;
            do {
                file << current->data << std::endl;
                current = current->next;
                if (current == head) break;
            } while (current != head);
        } else {
            Node* current = head;
            while (current != nullptr) {
                file << current->data << std::endl;
                current = current->next;
            }
        }

        file.close();
    }

    // из файла
    void readFromFile(const std::string& filename) {
        if (!isEmpty()) {
            throw std::runtime_error("Cannot load list from file: current list is not empty");
        }

        std::ifstream file(filename);
        if (!file.is_open()) {
            throw std::runtime_error("Failed to open file for reading");
        }

        std::string line;

        if (!std::getline(file, line)) {
            throw std::runtime_error("File is empty or has incorrect format");
        }


        int fileType = 1;
        if (line == ">") fileType = 1;
        else if (line == "<>") fileType = 2;
        else if (line == ">0") fileType = 3;
        else if (line == "<>0") fileType = 4;
        else throw std::runtime_error("Invalid list type in file");

        if (fileType != type) {
            std::cout << "Warning: List type in file (" << fileType
                      << ") differs from current (" << type
                      << "). Changing list type." << std::endl;
            type = fileType;
        }

        while (std::getline(file, line)) {
            if (!line.empty()) {
                T value;
                std::stringstream ss(line);
                ss >> value;
                addElement(value);
            }
        }

        file.close();
    }

    bool isEmpty() const {
        return head == nullptr;
    }

    int getType() const { return type; }
    int getSize() const { return size; }

    void setType(int newType) {
        if (!isEmpty()) {
            throw std::runtime_error("Cannot change type of non-empty list");
        }

        if (newType < 1 || newType > 4) {
            throw std::invalid_argument("Invalid list type. Valid values: 1-4");
        }

        type = newType;
    }
};

void parseCommandLine(int argc, char* argv[], int& listType, int& count, std::vector<std::string>& elements) {
    for (int i = 1; i < argc; i++) {
        if (std::strcmp(argv[i], "-t") == 0 && i + 1 < argc) {
            listType = std::atoi(argv[i + 1]);
            i++;
        } else if (std::strcmp(argv[i], "-c") == 0 && i + 1 < argc) {
            count = std::atoi(argv[i + 1]);
            i++;
        } else if (std::strcmp(argv[i], "-e") == 0 && i + 1 < argc) {
            std::string elementsStr = argv[i + 1];
            std::stringstream ss(elementsStr);
            std::string element;

            while (std::getline(ss, element, ',')) {
                elements.push_back(element);
            }
            i++;
        } else {
            throw std::invalid_argument("Invalid parameter: " + std::string(argv[i]));
        }
    }
}

// меню
template<typename T>
void displayMenu(LinkedList<T>& list) {
    int choice;
    T value;
    std::string filename;

    while (true) {
        std::cout << "\n=== We have it on the menu today:) ===" << std::endl;
        std::cout << "List type: ";
        switch (list.getType()) {
            case 1: std::cout << "Singly-linked"; break;
            case 2: std::cout << "Doubly-linked"; break;
            case 3: std::cout << "Circular singly-linked"; break;
            case 4: std::cout << "Circular doubly-linked"; break;
        }
        std::cout << " (size: " << list.getSize() << ")" << std::endl;

        std::cout << "1. Add element" << std::endl;
        std::cout << "2. Print list" << std::endl;
        std::cout << "3. Find element" << std::endl;
        std::cout << "4. Delete first occurrence of element" << std::endl;
        std::cout << "5. Delete all occurrences of element" << std::endl;
        std::cout << "6. Clear list" << std::endl;
        std::cout << "7. Change list type" << std::endl;
        std::cout << "8. Save list to file" << std::endl;
        std::cout << "9. Load list from file" << std::endl;
        std::cout << "0. Exit" << std::endl;
        std::cout << "Select action: ";

        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please try again." << std::endl;
            continue;
        }

        if (choice == 0) {
            break;
        }

        try {
            switch (choice) {
                case 1:
                    std::cout << "Enter value to add: ";
                    std::cin >> value;
                    list.addElement(value);
                    std::cout << "Element added." << std::endl;
                    break;

                case 2:
                    std::cout << "Current list:" << std::endl;
                    list.printList();
                    break;

                case 3:
                    std::cout << "Enter value to find: ";
                    std::cin >> value;
                    {
                        std::vector<int> positions = list.findElement(value);
                        if (positions.empty()) {
                            std::cout << "Element not found." << std::endl;
                        } else {
                            std::cout << "Element found at positions: ";
                            for (size_t i = 0; i < positions.size(); i++) {
                                std::cout << positions[i];
                                if (i < positions.size() - 1) std::cout << ", ";
                            }
                            std::cout << std::endl;
                        }
                    }
                    break;

                case 4:
                    std::cout << "Enter value to delete: ";
                    std::cin >> value;
                    if (list.deleteFirstOccurrence(value)) {
                        std::cout << "First occurrence of element deleted." << std::endl;
                    } else {
                        std::cout << "Element not found." << std::endl;
                    }
                    break;

                case 5:
                    std::cout << "Enter value to delete: ";
                    std::cin >> value;
                    {
                        int deletedCount = list.deleteAllOccurrences(value);
                        std::cout << "Deleted " << deletedCount << " occurrences of element." << std::endl;
                    }
                    break;

                case 6:
                    list.clear();
                    std::cout << "List cleared." << std::endl;
                    break;

                case 7:
                    if (!list.isEmpty()) {
                        std::cout << "Error: Cannot change type of non-empty list." << std::endl;
                    } else {
                        int newType;
                        std::cout << "Enter new list type:" << std::endl;
                        std::cout << "1. Singly-linked" << std::endl;
                        std::cout << "2. Doubly-linked" << std::endl;
                        std::cout << "3. Circular singly-linked" << std::endl;
                        std::cout << "4. Circular doubly-linked" << std::endl;
                        std::cout << "Choice: ";
                        std::cin >> newType;

                        list.setType(newType);
                        std::cout << "List type changed." << std::endl;
                    }
                    break;

                case 8:
                    std::cout << "Enter filename to save: ";
                    std::cin >> filename;
                    list.saveToFile(filename);
                    std::cout << "List saved to file." << std::endl;
                    break;

                case 9:
                    std::cout << "Enter filename to load: ";
                    std::cin >> filename;
                    list.readFromFile(filename);
                    std::cout << "List loaded from file." << std::endl;
                    break;

                default:
                    std::cout << "Invalid choice. Please try again." << std::endl;
            }
        } catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << std::endl;
        }

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

int main(int argc, char* argv[]) {
    try {
        int listType = 1;
        int count = 0;
        std::vector<std::string> elements;

        if (argc > 1) {
            parseCommandLine(argc, argv, listType, count, elements);

            if (listType < 1 || listType > 4) {
                throw std::invalid_argument("Invalid list type. Valid values: 1, 2, 3, 4");
            }
            if (count != static_cast<int>(elements.size())) {
                throw std::invalid_argument("Number of elements does not match -c parameter value");
            }
        }
        LinkedList<std::string> list(listType);

        for (const std::string& element : elements) {
            list.addElement(element);
        }
        displayMenu(list);
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}