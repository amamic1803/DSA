#include "binary_search_tree.hpp"
#include "tests.hpp"
#include <stdexcept>
#include <string>
#include <utility>


int main(const int argc, char *argv[]) {
    if (argc != 2) {
        return -2;
    }

    int arg;
    try {
        arg = std::stoi(argv[1]);
    } catch (const std::invalid_argument &e) {
        return -4;
    } catch (const std::out_of_range &e) {
        return -5;
    }

    bool test_result;
    switch (arg) {
        case 1:
            test_result = test_1();
            break;
        case 2:
            test_result = test_2();
            break;
        case 3:
            test_result = test_3();
            break;
        case 4:
            test_result = test_4();
            break;
        case 5:
            test_result = test_5();
            break;
        case 6:
            test_result = test_6();
            break;
        case 7:
            test_result = test_7();
            break;
        case 8:
            test_result = test_8();
            break;
        default:
            return -3;
    }

    return test_result ? 0 : -1;
}

bool test_1() {
    BinarySearchTree<int> tree;
    tree.insert(5);
    tree.insert(3);
    tree.insert(7);
    tree.insert(2);
    tree.insert(4);
    tree.insert(6);
    tree.insert(8);
    return tree.size() == 7 && !tree.empty() &&
    tree.search(5) && tree.search(3) && tree.search(7) && tree.search(2)
    && tree.search(4) && tree.search(6) && tree.search(8)
    && !tree.search(1) && !tree.search(9) && tree.balanced();
}

bool test_2() {
    // test copy constructor
    BinarySearchTree<int> tree;
    tree.insert(5);
    tree.insert(3);
    tree.insert(7);
    tree.insert(2);
    tree.insert(4);
    tree.insert(6);
    tree.insert(8);
    BinarySearchTree<int> tree2 = tree;
    return tree.size() == 7 && !tree.empty() &&
           tree.search(5) && tree.search(3) && tree.search(7) && tree.search(2)
           && tree.search(4) && tree.search(6) && tree.search(8)
           && !tree.search(1) && !tree.search(9) && tree.balanced()
    && tree2.size() == 7 && !tree2.empty() &&
    tree2.search(5) && tree2.search(3) && tree2.search(7) && tree2.search(2)
    && tree2.search(4) && tree2.search(6) && tree2.search(8)
    && !tree2.search(1) && !tree2.search(9) && tree2.balanced();
}

bool test_3() {
    // test copy assignment
    BinarySearchTree<int> tree;
    tree.insert(5);
    tree.insert(3);
    tree.insert(7);
    tree.insert(2);
    tree.insert(4);
    tree.insert(6);
    tree.insert(8);
    BinarySearchTree<int> tree2;
    tree2.insert(1);
    tree2.insert(9);
    tree2 = tree;

    return tree.size() == 7 && !tree.empty() &&
           tree.search(5) && tree.search(3) && tree.search(7) && tree.search(2)
           && tree.search(4) && tree.search(6) && tree.search(8)
           && !tree.search(1) && !tree.search(9) && tree.balanced()
    && tree2.size() == 7 && !tree2.empty() &&
    tree2.search(5) && tree2.search(3) && tree2.search(7) && tree2.search(2)
    && tree2.search(4) && tree2.search(6) && tree2.search(8)
    && !tree2.search(1) && !tree2.search(9) && tree2.balanced();
}

bool test_4() {
    // test move constructor
    BinarySearchTree<int> tree;
    tree.insert(5);
    tree.insert(3);
    tree.insert(7);
    tree.insert(2);
    tree.insert(4);
    tree.insert(6);
    tree.insert(8);
    BinarySearchTree<int> tree2 = std::move(tree);
    return tree.empty() && tree.balanced() &&
    tree2.size() == 7 && !tree2.empty() &&
    tree2.search(5) && tree2.search(3) && tree2.search(7) && tree2.search(2)
    && tree2.search(4) && tree2.search(6) && tree2.search(8)
    && !tree2.search(1) && !tree2.search(9) && tree2.balanced();
}

bool test_5() {
    // test move assignment
    BinarySearchTree<int> tree;
    tree.insert(5);
    tree.insert(3);
    tree.insert(7);
    tree.insert(2);
    tree.insert(4);
    tree.insert(6);
    tree.insert(8);
    BinarySearchTree<int> tree2;
    tree2.insert(1);
    tree2.insert(9);
    tree2 = std::move(tree);
    return tree.empty() && tree.balanced() &&
    tree2.size() == 7 && !tree2.empty() &&
    tree2.search(5) && tree2.search(3) && tree2.search(7) && tree2.search(2)
    && tree2.search(4) && tree2.search(6) && tree2.search(8)
    && !tree2.search(1) && !tree2.search(9) && tree2.balanced();
}

bool test_6() {
    // test traversing
    BinarySearchTree<int> tree;
    tree.insert(5);
    tree.insert(3);
    tree.insert(7);
    tree.insert(2);
    tree.insert(4);
    tree.insert(6);
    tree.insert(8);

    const std::string expectedPreorder = "5324768";
    const std::string expectedInorder = "2345678";
    const std::string expectedPostorder = "2436875";

    std::string preorder;
    tree.traversePreorder([&preorder](const int &value) {
        preorder += std::to_string(value);
    });

    std::string inorder;
    tree.traverseInorder([&inorder](const int &value) {
        inorder += std::to_string(value);
    });

    std::string postorder;
    tree.traversePostorder([&postorder](const int &value) {
        postorder += std::to_string(value);
    });

    return preorder == expectedPreorder && inorder == expectedInorder && postorder == expectedPostorder;
}

bool test_7() {
    // test remove
    BinarySearchTree<int> tree;
    tree.insert(5);
    tree.insert(3);
    tree.insert(7);
    tree.insert(2);
    tree.insert(4);
    tree.insert(6);
    tree.insert(8);

    tree.remove(5);
    tree.remove(4);
    tree.remove(6);
    tree.remove(8);

    return tree.size() == 3 && !tree.empty() &&
    tree.search(2) && tree.search(3) && tree.search(7) &&
    !tree.search(5) && !tree.search(4) && !tree.search(6) && !tree.search(8);
}

bool test_8() {
    // test balancing
    BinarySearchTree<int> tree;
    tree.insert(1);
    tree.insert(2);
    tree.insert(3);
    tree.insert(4);
    tree.insert(5);
    tree.insert(6);
    tree.insert(7);
    if (tree.balanced()) {
        return false;
    }
    tree.balance();
    return tree.balanced();
}
