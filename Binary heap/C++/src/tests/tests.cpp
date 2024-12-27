#include "binary_heap.hpp"
#include "tests.hpp"
#include <array>
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
    // test default constructor
    const BinaryHeap<int> heap;
    return heap.empty();
}

bool test_2() {
    // test copy constructor
    BinaryHeap<int> heap;
    heap.insert(1);
    heap.insert(2);
    heap.insert(3);
    const BinaryHeap<int> heap2(heap);

    return heap.size() == 3 && heap.peek() == 3 && heap.search(1) && heap.search(2) && heap.search(3) && !heap.search(0)
    && heap2.size() == 3 && heap2.peek() == 3 && heap2.search(1) && heap2.search(2) && heap2.search(3) && !heap2.search(0);
}

bool test_3() {
    // test move constructor
    BinaryHeap<int> heap;
    heap.insert(1);
    heap.insert(2);
    heap.insert(3);
    const BinaryHeap<int> heap2(std::move(heap));

    return heap.empty() && heap2.size() == 3 && heap2.peek() == 3 && heap2.search(1) && heap2.search(2) && heap2.search(3) && !heap2.search(0);
}

bool test_4() {
    // test copy assignment
    BinaryHeap<int> heap;
    heap.insert(1);
    heap.insert(2);
    heap.insert(3);
    BinaryHeap<int> heap2;
    heap2 = heap;

    return heap.size() == 3 && heap.peek() == 3 && heap.search(1) && heap.search(2) && heap.search(3) && !heap.search(0)
    && heap2.size() == 3 && heap2.peek() == 3 && heap2.search(1) && heap2.search(2) && heap2.search(3) && !heap2.search(0);
}

bool test_5() {
    // test move assignment
    BinaryHeap<int> heap;
    heap.insert(1);
    heap.insert(2);
    heap.insert(3);
    BinaryHeap<int> heap2;
    heap2 = std::move(heap);

    return heap.empty() && heap2.size() == 3 && heap2.peek() == 3 && heap2.search(1) && heap2.search(2) && heap2.search(3) && !heap2.search(0);
}

bool test_6() {
    // test insert, pop, peek
    BinaryHeap<int> heap;
    heap.insert(1);
    heap.insert(2);
    heap.insert(3);
    heap.insert(4);
    heap.insert(5);
    heap.insert(6);
    heap.insert(7);

    for (int i = 7; i >= 1; i--) {
        if (heap.peek() != i) {
            return false;
        }
        if (heap.pop() != i) {
            return false;
        }
    }

    return heap.empty();
}

bool test_7() {
    // test O(n) heap construction
    const std::array<int, 7> arr {1, 2, 3, 4, 5, 6, 7};

    BinaryHeap<int> heap(arr.data(), arr.size());

    for (int i = 7; i >= 1; i--) {
        if (heap.peek() != i) {
            return false;
        }
        if (heap.pop() != i) {
            return false;
        }
    }

    return heap.empty();
}

bool test_8() {
    // more complex test
    const std::array<int, 7> init_arr {1, 2, 3, 4, 5, 6, 7};
    BinaryHeap<int> heap(init_arr.data(), init_arr.size());
    for (int i = heap.size() + 1; i <= 100; i++) {
        heap.insert(i);
    }

    for (int i = heap.size(); i >= 1; i--) {
        if (heap.peek() != i) {
            return false;
        }
        if (heap.pop() != i) {
            return false;
        }
    }

    return heap.empty();
}
