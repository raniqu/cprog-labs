#include "BSTree.hpp"
#include <iostream>

int main() {
    using namespace trees;
    
    BSTree<int> tree;
    
    // Adding elements
    tree.add(50);
    tree.add(30);
    tree.add(70);
    tree.add(20);
    tree.add(40);
    tree.add(60);
    tree.add(80);

    std::cout << "In-order traversal (sorted): ";
    tree.printInOrder();
    std::cout << std::endl;

    std::cout << "Pre-order traversal: ";
    tree.printPreOrder();
    std::cout << std::endl;

    std::cout << "Post-order traversal: ";
    tree.printPostOrder();
    std::cout << std::endl;

    std::cout << "Tree via operator<<: " << tree << std::endl;

    std::cout << "Search for 40: " << (tree.find(40) ? "found" : "not found") << std::endl;
    std::cout << "Search for 100: " << (tree.find(100) ? "found" : "not found") << std::endl;

    tree.remove(30);
    std::cout << "After removing 30: " << tree << std::endl;

    tree.saveToFile("tree.txt");
    std::cout << "Tree saved to 'tree.txt'" << std::endl;

    BSTree<int> tree2;
    tree2.loadFromFile("tree.txt");
    std::cout << "Loaded from file: " << tree2 << std::endl;


    BSTree<int> tree3(tree2);
    std::cout << "Copy of tree2: " << tree3 << std::endl;


    BSTree<int> tree4(std::move(tree3));
    std::cout << "After move (tree4): " << tree4 << std::endl;
    std::cout << "tree3 is now empty: " << tree3 << std::endl;


    tree4.clearTree();
    std::cout << "After clearing tree4: " << tree4 << std::endl;


    BSTree<int> tree5;
    tree5 = tree2;
    std::cout << "Copy assignment (tree5 = tree2): " << tree5 << std::endl;


    BSTree<int> tree6;
    tree6 = std::move(tree5);
    std::cout << "Move assignment (tree6 = move(tree5)): " << tree6 << std::endl;
    std::cout << "tree5 is now empty: " << tree5 << std::endl;
    
    return 0;
}