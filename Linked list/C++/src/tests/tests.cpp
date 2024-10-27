#include "linked_list.hpp"
#include "tests.hpp"
#include <string>

int main(const int argc, char *argv[]) {
    if (argc != 2) {
        return -2;
    }

    const std::string arg(argv[1]);
    bool test_result;

    if (arg == "seq1")
        test_result = test_seq1();
    else
        return -3;

    return test_result ? 0 : -1;
}

bool test_seq1() {
    LinkedList<int> *list = new SinglyLinkedList<int>();
    return false;
}
