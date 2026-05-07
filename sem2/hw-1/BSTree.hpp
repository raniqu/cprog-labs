#ifndef BSTREE_HPP
#define BSTREE_HPP

#include <iostream>
#include <fstream>
#include <string>

namespace trees {

template <typename T>
class BSTree {
private:
    struct Node {
        T data;
        Node* left;
        Node* right;
        Node(const T& val) : data(val), left(nullptr), right(nullptr) {}
    };

    Node* root;


    void clear(Node* node) {
        if (!node) return;
        clear(node->left);
        clear(node->right);
        delete node;
    }

    Node* copy(Node* node) {
        if (!node) return nullptr;
        Node* newNode = new Node(node->data);
        newNode->left = copy(node->left);
        newNode->right = copy(node->right);
        return newNode;
    }

    Node* insert(Node* node, const T& val) {
        if (!node) return new Node(val);
        if (val < node->data)
            node->left = insert(node->left, val);
        else if (val > node->data)
            node->right = insert(node->right, val);
        return node;
    }

    Node* findMin(Node* node) {
        while (node->left) node = node->left;
        return node;
    }

    Node* remove(Node* node, const T& val, bool& removed) {
        if (!node) return nullptr;

        if (val < node->data)
            node->left = remove(node->left, val, removed);
        else if (val > node->data)
            node->right = remove(node->right, val, removed);
        else {
            removed = true;
            if (!node->left) {
                Node* right = node->right;
                delete node;
                return right;
            }
            if (!node->right) {
                Node* left = node->left;
                delete node;
                return left;
            }
            Node* min = findMin(node->right);
            node->data = min->data;
            node->right = remove(node->right, min->data, removed);
        }
        return node;
    }

    bool search(Node* node, const T& val) const {
        if (!node) return false;
        if (val == node->data) return true;
        if (val < node->data) return search(node->left, val);
        return search(node->right, val);
    }

    void preOrder(Node* node, std::ostream& os) const {
        if (!node) return;
        os << node->data << " ";
        preOrder(node->left, os);
        preOrder(node->right, os);
    }

    void inOrder(Node* node, std::ostream& os) const {
        if (!node) return;
        inOrder(node->left, os);
        os << node->data << " ";
        inOrder(node->right, os);
    }

    void postOrder(Node* node, std::ostream& os) const {
        if (!node) return;
        postOrder(node->left, os);
        postOrder(node->right, os);
        os << node->data << " ";
    }

    void save(Node* node, std::ofstream& ofs) const {
        if (!node) {
            ofs << "()";
            return;
        }
        ofs << "(" << node->data;
        save(node->left, ofs);
        save(node->right, ofs);
        ofs << ")";
    }

    Node* load(std::ifstream& ifs) {
        char c;
        ifs >> c;
        if (c != '(') return nullptr;

        ifs >> c;
        if (c == ')') return nullptr;

        ifs.putback(c);
        T val;
        ifs >> val;

        Node* node = new Node(val);
        node->left = load(ifs);
        node->right = load(ifs);

        ifs >> c;
        return node;
    }

public:

    BSTree() : root(nullptr) {}


    BSTree(const BSTree& other) : root(nullptr) {
        if (other.root) {
            root = copy(other.root);
        }
    }


    BSTree(BSTree&& other) noexcept : root(other.root) {
        other.root = nullptr;
    }


    ~BSTree() {
        clear(root);
    }


    BSTree& operator=(const BSTree& other) {
        if (this != &other) {
            clear(root);
            root = other.root ? copy(other.root) : nullptr;
        }
        return *this;
    }


    BSTree& operator=(BSTree&& other) noexcept {
        if (this != &other) {
            clear(root);
            root = other.root;
            other.root = nullptr;
        }
        return *this;
    }


    void add(const T& val) {
        root = insert(root, val);
    }


    bool remove(const T& val) {
        bool removed = false;
        root = remove(root, val, removed);
        return removed;
    }


    void clearTree() {
        clear(root);
        root = nullptr;
    }


    bool find(const T& val) const {
        return search(root, val);
    }


    void printPreOrder(std::ostream& os = std::cout) const {
        preOrder(root, os);
    }


    void printInOrder(std::ostream& os = std::cout) const {
        inOrder(root, os);
    }


    void printPostOrder(std::ostream& os = std::cout) const {
        postOrder(root, os);
    }


    bool saveToFile(const std::string& filename) const {
        std::ofstream ofs(filename);
        if (!ofs.is_open()) return false;
        save(root, ofs);
        return !ofs.fail();
    }


    bool loadFromFile(const std::string& filename) {
        std::ifstream ifs(filename);
        if (!ifs.is_open()) return false;

        clearTree();
        root = load(ifs);
        return !ifs.fail();
    }


    friend std::ostream& operator<<(std::ostream& os, const BSTree& tree) {
        tree.printInOrder(os);
        return os;
    }
};

}

#endif