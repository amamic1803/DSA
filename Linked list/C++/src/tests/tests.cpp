#include "linked_list.hpp"
#include "tests.hpp"
#include <string>
#include <utility>


// NOLINTBEGIN(bugprone-exception-escape)
int main(const int argc, char *argv[]) {
    if (argc != 2) {
        return -2;
    }

    const std::string arg(argv[1]);
    bool test_result = false;

    if (arg == "SinglyLinkedList1") {
        test_result = test_SinglyLinkedList1();
    } else if (arg == "SinglyLinkedList2") {
        test_result = test_SinglyLinkedList2();
    } else if (arg == "SinglyLinkedList3") {
        test_result = test_SinglyLinkedList3();
    } else if (arg == "SinglyLinkedList4") {
        test_result = test_SinglyLinkedList4();
    } else if (arg == "SinglyLinkedList5") {
        test_result = test_SinglyLinkedList5();
    } else if (arg == "SinglyLinkedList6") {
        test_result = test_SinglyLinkedList6();
    } else if (arg == "DoublyLinkedList1") {
        test_result = test_DoublyLinkedList1();
    } else if (arg == "DoublyLinkedList2") {
        test_result = test_DoublyLinkedList2();
    } else if (arg == "DoublyLinkedList3") {
        test_result = test_DoublyLinkedList3();
    } else if (arg == "DoublyLinkedList4") {
        test_result = test_DoublyLinkedList4();
    } else if (arg == "DoublyLinkedList5") {
        test_result = test_DoublyLinkedList5();
    } else if (arg == "DoublyLinkedList6") {
        test_result = test_DoublyLinkedList6();
    } else {
        return -3;
    }

    return test_result ? 0 : -1;
}
// NOLINTEND(bugprone-exception-escape)


// NOLINTBEGIN(bugprone-use-after-move,hicpp-invalid-access-moved)

bool test_SinglyLinkedList1() {
    SinglyLinkedList<int> list;
    list.insert(0, 1);
    list.insert(1, 2);
    list.insert(2, 3);
    return list.get(0) == 1 && list.get(1) == 2 && list.get(2) == 3;
}

bool test_SinglyLinkedList2() {
    SinglyLinkedList<int> list;
    list.insert(0, 1);
    list.insert(1, 2);
    list.insert(2, 3);
    list.erase(1);
    return list.get(0) == 1 && list.get(1) == 3;
}

bool test_SinglyLinkedList3() {
    SinglyLinkedList<int> list1;
    list1.insert(0, 1);
    list1.insert(1, 2);
    const SinglyLinkedList<int> list2 = list1;
    return list2.get(0) == 1 && list2.get(1) == 2;
}

bool test_SinglyLinkedList4() {
    SinglyLinkedList<int> list1;
    list1.insert(0, 1);
    list1.insert(1, 2);
    SinglyLinkedList<int> list2;
    list2 = list1;
    return list2.get(0) == 1 && list2.get(1) == 2;
}

bool test_SinglyLinkedList5() {
    SinglyLinkedList<int> list1;
    list1.insert(0, 1);
    list1.insert(1, 2);
    const SinglyLinkedList<int> list2 = std::move(list1);
    return list2.get(0) == 1 && list2.get(1) == 2 && list1.empty();
}

bool test_SinglyLinkedList6() {
    SinglyLinkedList<int> list1;
    list1.insert(0, 1);
    list1.insert(1, 2);
    SinglyLinkedList<int> list2;
    list2 = std::move(list1);
    return list2.get(0) == 1 && list2.get(1) == 2 && list1.empty();
}

bool test_DoublyLinkedList1() {
    DoublyLinkedList<int> list;
    list.insert(0, 1);
    list.insert(1, 2);
    list.insert(2, 3);
    return list.get(0) == 1 && list.get(1) == 2 && list.get(2) == 3;
}

bool test_DoublyLinkedList2() {
    DoublyLinkedList<int> list;
    list.insert(0, 1);
    list.insert(1, 2);
    list.insert(2, 3);
    list.erase(1);
    return list.get(0) == 1 && list.get(1) == 3;
}

bool test_DoublyLinkedList3() {
    DoublyLinkedList<int> list1;
    list1.insert(0, 1);
    list1.insert(1, 2);
    const DoublyLinkedList<int> list2 = list1;
    return list2.get(0) == 1 && list2.get(1) == 2;
}

bool test_DoublyLinkedList4() {
    DoublyLinkedList<int> list1;
    list1.insert(0, 1);
    list1.insert(1, 2);
    DoublyLinkedList<int> list2;
    list2 = list1;
    return list2.get(0) == 1 && list2.get(1) == 2;
}

bool test_DoublyLinkedList5() {
    DoublyLinkedList<int> list1;
    list1.insert(0, 1);
    list1.insert(1, 2);
    const DoublyLinkedList<int> list2 = std::move(list1);
    return list2.get(0) == 1 && list2.get(1) == 2 && list1.empty();
}

bool test_DoublyLinkedList6() {
    DoublyLinkedList<int> list1;
    list1.insert(0, 1);
    list1.insert(1, 2);
    DoublyLinkedList<int> list2;
    list2 = std::move(list1);
    return list2.get(0) == 1 && list2.get(1) == 2 && list1.empty();
}

// NOLINTEND(bugprone-use-after-move,hicpp-invalid-access-moved)
