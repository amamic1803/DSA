#include "stack.hpp"
#include "tests.hpp"
#include <exception>
#include <iostream>
#include <string>
#include <utility>

// NOLINTBEGIN(bugprone-exception-escape)
int main(const int argc, char *argv[]) {
    try {
        if (argc != 2) {
            return -2;
        }
        const std::string test_name(argv[1]);

        if (test_name == "ListStack1") {
            return test_ListStack1() ? 0 : -1;
        }
        if (test_name == "ListStack2") {
            return test_ListStack2() ? 0 : -1;
        }
        if (test_name == "ListStack3") {
            return test_ListStack3() ? 0 : -1;
        }
        if (test_name == "ListStack4") {
            return test_ListStack4() ? 0 : -1;
        }
        if (test_name == "ListStack5") {
            return test_ListStack5() ? 0 : -1;
        }
        if (test_name == "ListStack6") {
            return test_ListStack6() ? 0 : -1;
        }
        if (test_name == "StaticStack1") {
            return test_StaticStack1() ? 0 : -1;
        }
        if (test_name == "StaticStack2") {
            return test_StaticStack2() ? 0 : -1;
        }
        if (test_name == "StaticStack3") {
            return test_StaticStack3() ? 0 : -1;
        }
        if (test_name == "StaticStack4") {
            return test_StaticStack4() ? 0 : -1;
        }
        if (test_name == "StaticStack5") {
            return test_StaticStack5() ? 0 : -1;
        }
        if (test_name == "StaticStack6") {
            return test_StaticStack6() ? 0 : -1;
        }
        if (test_name == "DynamicStack1") {
            return test_DynamicStack1() ? 0 : -1;
        }
        if (test_name == "DynamicStack2") {
            return test_DynamicStack2() ? 0 : -1;
        }
        if (test_name == "DynamicStack3") {
            return test_DynamicStack3() ? 0 : -1;
        }
        if (test_name == "DynamicStack4") {
            return test_DynamicStack4() ? 0 : -1;
        }
        if (test_name == "DynamicStack5") {
            return test_DynamicStack5() ? 0 : -1;
        }
        if (test_name == "DynamicStack6") {
            return test_DynamicStack6() ? 0 : -1;
        }
    } catch (const std::exception& e) {
        std::cerr << "Exception caught: " << e.what() << '\n';
        return -4;
    } catch (...) {
        // Catch all other exceptions
        std::cerr << "Unknown exception caught." << '\n';
        return -5;
    }

    return -3;
}
// NOLINTEND(bugprone-exception-escape)


// NOLINTBEGIN(bugprone-use-after-move,hicpp-invalid-access-moved,clang-analyzer-cplusplus.Move)

bool test_ListStack1() {
    // test ListStack with int

    ListStack<int> s;

    if (!s.isEmpty()) {
        return false;
    }
    if (s.size() != 0) {
        return false;
    }

    if (!s.push(1)) {
        return false;
    }
    if (!s.push(2)) {
        return false;
    }
    if (!s.push(3)) {
        return false;
    }

    int value = 0;

    if (!s.peek(value) || value != 3) {
        return false;
    }

    if (!s.pop(value) || value != 3) {
        return false;
    }
    if (!s.pop(value) || value != 2) {
        return false;
    }
    if (!s.pop(value) || value != 1) {
        return false;
    }
    if (s.pop(value)) {
        return false;
    }

    if (s.size() != 0) {
        return false;
    }
    if (!s.isEmpty()) {
        return false;
    }

    if (!s.push(1)) {
        return false;
    }
    if (!s.push(2)) {
        return false;
    }
    if (!s.push(3)) {
        return false;
    }

    s.clear();
    if (s.size() != 0) {
        return false;
    }
    if (!s.isEmpty()) {
        return false;
    }

    if (s.pop(value)) {
        return false;
    }

    return true;
}

bool test_ListStack2() {
    // test ListStack with std::string

    ListStack<std::string> s;

    if (!s.isEmpty()) {
        return false;
    }
    if (s.size() != 0) {
        return false;
    }

    if (!s.push("1")) {
        return false;
    }
    if (!s.push("2")) {
        return false;
    }
    if (!s.push("3")) {
        return false;
    }

    std::string value;

    if (!s.peek(value) || value != "3") {
        return false;
    }

    if (!s.pop(value) || value != "3") {
        return false;
    }
    if (!s.pop(value) || value != "2") {
        return false;
    }
    if (!s.pop(value) || value != "1") {
        return false;
    }
    if (s.pop(value)) {
        return false;
    }

    if (s.size() != 0) {
        return false;
    }
    if (!s.isEmpty()) {
        return false;
    }

    if (!s.push("1")) {
        return false;
    }
    if (!s.push("2")) {
        return false;
    }
    if (!s.push("3")) {
        return false;
    }

    s.clear();
    if (s.size() != 0) {
        return false;
    }
    if (!s.isEmpty()) {
        return false;
    }

    if (s.pop(value)) {
        return false;
    }

    return true;
}

bool test_ListStack3() {
    // test ListStack through Stack interface with int

    Stack<int>* s = new ListStack<int>();

    if (!s->isEmpty()) {
        delete s;
        return false;
    }
    if (s->size() != 0) {
        delete s;
        return false;
    }

    if (!s->push(1)) {
        delete s;
        return false;
    }
    if (!s->push(2)) {
        delete s;
        return false;
    }
    if (!s->push(3)) {
        delete s;
        return false;
    }

    int value = 0;

    if (!s->peek(value) || value != 3) {
        delete s;
        return false;
    }

    if (!s->pop(value) || value != 3) {
        delete s;
        return false;
    }
    if (!s->pop(value) || value != 2) {
        delete s;
        return false;
    }
    if (!s->pop(value) || value != 1) {
        delete s;
        return false;
    }
    if (s->pop(value)) {
        delete s;
        return false;
    }

    if (s->size() != 0) {
        delete s;
        return false;
    }
    if (!s->isEmpty()) {
        delete s;
        return false;
    }

    if (!s->push(1)) {
        delete s;
        return false;
    }
    if (!s->push(2)) {
        delete s;
        return false;
    }
    if (!s->push(3)) {
        delete s;
        return false;
    }

    s->clear();

    if (s->size() != 0) {
        delete s;
        return false;
    }
    if (!s->isEmpty()) {
        delete s;
        return false;
    }

    if (s->pop(value)) {
        delete s;
        return false;
    }

    delete s;

    return true;
}

bool test_ListStack4() {
    // test ListStack through Stack interface with std::string

    Stack<std::string>* s = new ListStack<std::string>();

    if (!s->isEmpty()) {
        delete s;
        return false;
    }
    if (s->size() != 0) {
        delete s;
        return false;
    }

    if (!s->push("1")) {
        delete s;
        return false;
    }
    if (!s->push("2")) {
        delete s;
        return false;
    }
    if (!s->push("3")) {
        delete s;
        return false;
    }

    std::string value;

    if (!s->peek(value) || value != "3") {
        delete s;
        return false;
    }

    if (!s->pop(value) || value != "3") {
        delete s;
        return false;
    }
    if (!s->pop(value) || value != "2") {
        delete s;
        return false;
    }
    if (!s->pop(value) || value != "1") {
        delete s;
        return false;
    }
    if (s->pop(value)) {
        delete s;
        return false;
    }

    if (s->size() != 0) {
        delete s;
        return false;
    }
    if (!s->isEmpty()) {
        delete s;
        return false;
    }

    if (!s->push("1")) {
        delete s;
        return false;
    }
    if (!s->push("2")) {
        delete s;
        return false;
    }
    if (!s->push("3")) {
        delete s;
        return false;
    }

    s->clear();

    if (s->size() != 0) {
        delete s;
        return false;
    }
    if (!s->isEmpty()) {
        delete s;
        return false;
    }

    if (s->pop(value)) {
        delete s;
        return false;
    }

    delete s;

    return true;
}

bool test_ListStack5() {
    // test copy and move semantics
    int value = 0;
    int value2 = 0;

    ListStack<int> s1;
    s1.push(1);
    s1.push(2);
    s1.push(3);

    ListStack<int> s2(s1);
    if (s1.size() != s2.size()) {
        return false;
    }
    if (s1.isEmpty() != s2.isEmpty()) {
        return false;
    }
    if (!s1.pop(value) || !s2.pop(value)) {
        return false;
    }
    if (s1.size() != s2.size()) {
        return false;
    }
    if (s1.isEmpty() != s2.isEmpty()) {
        return false;
    }

    ListStack<int> s3(std::move(s1));
    if (s1.size() != 0) {
        return false;
    }
    if (!s1.isEmpty()) {
        return false;
    }
    if (s3.size() != 2) {
        return false;
    }
    if (s3.isEmpty()) {
        return false;
    }
    if (!s3.pop(value)) {
        return false;
    }
    if (value != 2) {
        return false;
    }

    ListStack<int> s4;
    s4.push(4);
    s4.push(5);
    s4.push(6);
    s4 = s3;
    if (s3.size() != s4.size()) {
        return false;
    }
    if (s3.isEmpty() != s4.isEmpty()) {
        return false;
    }
    if (!s3.pop(value) || !s4.pop(value2)) {
        return false;
    }
    if (value != value2) {
        return false;
    }
    if (s3.size() != s4.size()) {
        return false;
    }
    if (s3.isEmpty() != s4.isEmpty()) {
        return false;
    }

    s4.clear();
    s4.push(4);
    s4.push(5);
    s4.push(6);

    ListStack<int> s5;
    s5.push(7);
    s5.push(8);
    s5.push(9);
    s5 = std::move(s4);
    if (s4.size() != 0) {
        return false;
    }
    if (!s4.isEmpty()) {
        return false;
    }
    if (s5.size() != 3) {
        return false;
    }
    if (s5.isEmpty()) {
        return false;
    }
    if (!s5.pop(value)) {
        return false;
    }
    if (value != 6) {
        return false;
    }

    return true;
}

bool test_ListStack6() {
    // test copy semantics through Stack interface
    // there are no move semantics to test here
    // (move is just moving the pointer to a Stack object)
    int value = 0;
    int value2 = 0;

    Stack<int>* s1 = new ListStack<int>();
    s1->push(1);
    s1->push(2);
    s1->push(3);

    Stack<int>* s2 = s1->clone();
    if (s1->size() != s2->size()) {
        delete s1;
        delete s2;
        return false;
    }
    if (s1->isEmpty() != s2->isEmpty()) {
        delete s1;
        delete s2;
        return false;
    }
    if (!s1->pop(value) || !s2->pop(value2)) {
        delete s1;
        delete s2;
        return false;
    }
    if (value != value2) {
        delete s1;
        delete s2;
        return false;
    }
    if (s1->size() != s2->size()) {
        delete s1;
        delete s2;
        return false;
    }
    if (s1->isEmpty() != s2->isEmpty()) {
        delete s1;
        delete s2;
        return false;
    }

    delete s1;
    delete s2;

    return true;
}

bool test_StaticStack1() {
    // test StaticStack with int

    StaticStack<int> s{3};

    if (!s.isEmpty() || s.size() != 0) {
        return false;
    }

    if (!s.push(1)) {
        return false;
    }
    if (!s.push(2)) {
        return false;
    }
    if (!s.push(3)) {
        return false;
    }
    if (s.push(4)) { // should be full
        return false;
    }
    if (!s.isFull()) { // should be full
        return false;
    }

    int value = 0;

    if (!s.peek(value) || value != 3) {
        return false;
    }

    if (!s.pop(value) || value != 3) {
        return false;
    }
    if (!s.pop(value) || value != 2) {
        return false;
    }
    if (!s.pop(value) || value != 1) {
        return false;
    }
    if (s.pop(value)) { // should be empty
        return false;
    }

    if (s.size() != 0) {
        return false;
    }
    if (!s.isEmpty()) {
        return false;
    }

    if (!s.push(1)) {
        return false;
    }
    if (!s.push(2)) {
        return false;
    }
    if (!s.push(3)) {
        return false;
    }

    s.clear();
    if (s.size() != 0) {
        return false;
    }
    if (!s.isEmpty()) {
        return false;
    }

    if (s.pop(value)) { // should be empty
        return false;
    }

    return true;
}

bool test_StaticStack2() {
    // test StaticStack with std::string

    StaticStack<std::string> s{3};

    if (!s.isEmpty()) {
        return false;
    }
    if (s.size() != 0) {
        return false;
    }

    if (!s.push("1")) {
        return false;
    }
    if (!s.push("2")) {
        return false;
    }
    if (!s.push("3")) {
        return false;
    }
    if (s.push("4")) { // should be full
        return false;
    }
    if (!s.isFull()) { // should be full
        return false;
    }

    std::string value;

    if (!s.peek(value) || value != "3") {
        return false;
    }

    if (!s.pop(value) || value != "3") {
        return false;
    }
    if (!s.pop(value) || value != "2") {
        return false;
    }
    if (!s.pop(value) || value != "1") {
        return false;
    }
    if (s.pop(value)) { // should be empty
        return false;
    }

    if (s.size() != 0) {
        return false;
    }
    if (!s.isEmpty()) {
        return false;
    }

    if (!s.push("1")) {
        return false;
    }
    if (!s.push("2")) {
        return false;
    }
    if (!s.push("3")) {
        return false;
    }

    s.clear();
    if (s.size() != 0) {
        return false;
    }
    if (!s.isEmpty()) {
        return false;
    }

    if (s.pop(value)) { // should be empty
        return false;
    }

    return true;
}

bool test_StaticStack3() {
    // test StaticStack through Stack interface with int

    Stack<int>* s = new StaticStack<int>(3);

    if (!s->isEmpty()) {
        delete s;
        return false;
    }
    if (s->size() != 0) {
        delete s;
        return false;
    }

    if (!s->push(1)) {
        delete s;
        return false;
    }
    if (!s->push(2)) {
        delete s;
        return false;
    }
    if (!s->push(3)) {
        delete s;
        return false;
    }
    if (s->push(4)) { // should be full
        delete s;
        return false;
    }
    if (!(dynamic_cast<StaticStack<int>*>(s))->isFull()) { // should be full
        delete s;
        return false;
    }

    int value = 0;

    if (!s->peek(value) || value != 3) {
        delete s;
        return false;
    }

    if (!s->pop(value) || value != 3) {
        delete s;
        return false;
    }
    if (!s->pop(value) || value != 2) {
        delete s;
        return false;
    }
    if (!s->pop(value) || value != 1) {
        delete s;
        return false;
    }
    if (s->pop(value)) { // should be empty
        delete s;
        return false;
    }

    if (s->size() != 0) {
        delete s;
        return false;
    }
    if (!s->isEmpty()) {
        delete s;
        return false;
    }

    if (!s->push(1)) {
        delete s;
        return false;
    }
    if (!s->push(2)) {
        delete s;
        return false;
    }
    if (!s->push(3)) {
        delete s;
        return false;
    }

    s->clear();

    if (s->size() != 0) {
        delete s;
        return false;
    }
    if (!s->isEmpty()) {
        delete s;
        return false;
    }

    if (s->pop(value)) { // should be empty
        delete s;
        return false;
    }

    delete s;

    return true;
}

bool test_StaticStack4() {
    // test StaticStack through Stack interface with std::string

    Stack<std::string>* s = new StaticStack<std::string>(3);

    if (!s->isEmpty()) {
        delete s;
        return false;
    }
    if (s->size() != 0) {
        delete s;
        return false;
    }

    if (!s->push("1")) {
        delete s;
        return false;
    }
    if (!s->push("2")) {
        delete s;
        return false;
    }
    if (!s->push("3")) {
        delete s;
        return false;
    }
    if (s->push("4")) { // should be full
        delete s;
        return false;
    }
    if (!(dynamic_cast<StaticStack<std::string>*>(s))->isFull()) { // should be full
        delete s;
        return false;
    }

    std::string value;

    if (!s->peek(value) || value != "3") {
        delete s;
        return false;
    }

    if (!s->pop(value) || value != "3") {
        delete s;
        return false;
    }
    if (!s->pop(value) || value != "2") {
        delete s;
        return false;
    }
    if (!s->pop(value) || value != "1") {
        delete s;
        return false;
    }
    if (s->pop(value)) { // should be empty
        delete s;
        return false;
    }

    if (s->size() != 0) {
        delete s;
        return false;
    }
    if (!s->isEmpty()) {
        delete s;
        return false;
    }

    if (!s->push("1")) {
        delete s;
        return false;
    }
    if (!s->push("2")) {
        delete s;
        return false;
    }
    if (!s->push("3")) {
        delete s;
        return false;
    }

    s->clear();

    if (s->size() != 0) {
        delete s;
        return false;
    }
    if (!s->isEmpty()) {
        delete s;
        return false;
    }

    if (s->pop(value)) { // should be empty
        delete s;
        return false;
    }

    delete s;

    return true;
}

bool test_StaticStack5() {
    // test copy and move semantics
    int value = 0;
    int value2 = 0;

    StaticStack<int> s1{3};
    s1.push(1);
    s1.push(2);
    s1.push(3);

    StaticStack<int> s2(s1);
    if (s1.size() != s2.size()) {
        return false;
    }
    if (s1.isEmpty() != s2.isEmpty()) {
        return false;
    }
    if (!s1.pop(value) || !s2.pop(value2)) {
        return false;
    }
    if (value != value2) {
        return false;
    }
    if (s1.size() != s2.size()) {
        return false;
    }
    if (s1.isEmpty() != s2.isEmpty()) {
        return false;
    }

    StaticStack<int> s3(std::move(s1));
    if (s1.size() != 0) {
        return false;
    }
    if (!s1.isEmpty()) {
        return false;
    }
    if (s3.size() != 2) {
        return false;
    }
    if (s3.isEmpty()) {
        return false;
    }
    if (!s3.pop(value)) {
        return false;
    }
    if (value != 2) {
        return false;
    }

    StaticStack<int> s4{3};
    s4.push(4);
    s4.push(5);
    s4.push(6);
    s4 = s3;
    if (s3.size() != s4.size()) {
        return false;
    }
    if (s3.isEmpty() != s4.isEmpty()) {
        return false;
    }
    if (!s3.pop(value) || !s4.pop(value2)) {
        return false;
    }
    if (value != value2) {
        return false;
    }
    if (value != 1) {
        return false;
    }
    if (s3.size() != s4.size()) {
        return false;
    }
    if (s3.isEmpty() != s4.isEmpty()) {
        return false;
    }

    s4.clear();
    s4.push(4);
    s4.push(5);
    s4.push(6);

    StaticStack<int> s5{3};
    s5.push(7);
    s5.push(8);
    s5.push(9);
    s5 = std::move(s4);
    if (s4.size() != 0) {
        return false;
    }
    if (!s4.isEmpty()) {
        return false;
    }
    if (s5.size() != 3) {
        return false;
    }
    if (s5.isEmpty()) {
        return false;
    }
    if (!s5.pop(value)) {
        return false;
    }
    if (value != 6) {
        return false;
    }

    return true;
}

bool test_StaticStack6() {
    // test copy semantics through Stack interface
    // there are no move semantics to test here
    // (move is just moving the pointer to a Stack object)
    int value = 0;
    int value2 = 0;

    Stack<int>* s1 = new StaticStack<int>(3);
    s1->push(1);
    s1->push(2);
    s1->push(3);

    Stack<int>* s2 = s1->clone();
    if (s1->size() != s2->size()) {
        delete s1;
        delete s2;
        return false;
    }
    if (s1->isEmpty() != s2->isEmpty()) {
        delete s1;
        delete s2;
        return false;
    }
    if (!s1->pop(value) || !s2->pop(value2)) {
        delete s1;
        delete s2;
        return false;
    }
    if (value != value2) {
        delete s1;
        delete s2;
        return false;
    }
    if (s1->size() != s2->size()) {
        delete s1;
        delete s2;
        return false;
    }
    if (s1->isEmpty() != s2->isEmpty()) {
        delete s1;
        delete s2;
        return false;
    }

    delete s1;
    delete s2;

    return true;
}

bool test_DynamicStack1() {
    // test DynamicStack with int

    DynamicStack<int> s{3};

    if (!s.isEmpty() || s.size() != 0) {
        return false;
    }

    if (!s.push(1)) {
        return false;
    }
    if (!s.push(2)) {
        return false;
    }
    if (!s.push(3)) {
        return false;
    }
    if (!s.push(4)) { // should resize
        return false;
    }
    if (s.capacity() <= 3) { // capacity should have increased
        return false;
    }

    int value = 0;

    if (!s.peek(value) || value != 4) {
        return false;
    }

    if (!s.pop(value) || value != 4) {
        return false;
    }
    if (!s.pop(value) || value != 3) {
        return false;
    }
    if (!s.pop(value) || value != 2) {
        return false;
    }
    if (!s.pop(value) || value != 1) {
        return false;
    }
    if (s.pop(value)) { // should be empty
        return false;
    }

    if (s.size() != 0) {
        return false;
    }
    if (!s.isEmpty()) {
        return false;
    }

    if (!s.push(1)) {
        return false;
    }
    if (!s.push(2)) {
        return false;
    }
    if (!s.push(3)) {
        return false;
    }

    s.clear();
    if (s.size() != 0) {
        return false;
    }
    if (!s.isEmpty()) {
        return false;
    }

    if (s.pop(value)) { // should be empty
        return false;
    }

    return true;
}

bool test_DynamicStack2() {
    // test DynamicStack with std::string

    DynamicStack<std::string> s{3};

    if (!s.isEmpty()) {
        return false;
    }
    if (s.size() != 0) {
        return false;
    }

    if (!s.push("1")) {
        return false;
    }
    if (!s.push("2")) {
        return false;
    }
    if (!s.push("3")) {
        return false;
    }
    if (!s.push("4")) { // should resize
        return false;
    }
    if (s.capacity() <= 3) { // capacity should have increased
        return false;
    }

    std::string value;

    if (!s.peek(value) || value != "4") {
        return false;
    }

    if (!s.pop(value) || value != "4") {
        return false;
    }
    if (!s.pop(value) || value != "3") {
        return false;
    }
    if (!s.pop(value) || value != "2") {
        return false;
    }
    if (!s.pop(value) || value != "1") {
        return false;
    }
    if (s.pop(value)) { // should be empty
        return false;
    }

    if (s.size() != 0) {
        return false;
    }
    if (!s.isEmpty()) {
        return false;
    }

    if (!s.push("1")) {
        return false;
    }
    if (!s.push("2")) {
        return false;
    }
    if (!s.push("3")) {
        return false;
    }

    s.clear();
    if (s.size() != 0) {
        return false;
    }
    if (!s.isEmpty()) {
        return false;
    }

    if (s.pop(value)) { // should be empty
        return false;
    }

    return true;
}

bool test_DynamicStack3() {
    // test DynamicStack through Stack interface with int

    Stack<int>* s = new DynamicStack<int>(3);

    if (!s->isEmpty()) {
        delete s;
        return false;
    }
    if (s->size() != 0) {
        delete s;
        return false;
    }

    if (!s->push(1)) {
        delete s;
        return false;
    }
    if (!s->push(2)) {
        delete s;
        return false;
    }
    if (!s->push(3)) {
        delete s;
        return false;
    }
    if (!s->push(4)) { // should resize
        delete s;
        return false;
    }
    if (dynamic_cast<DynamicStack<int>*>(s)->capacity() <= 3) { // capacity should have increased
        delete s;
        return false;
    }

    int value = 0;

    if (!s->peek(value) || value != 4) {
        delete s;
        return false;
    }

    if (!s->pop(value) || value != 4) {
        delete s;
        return false;
    }
    if (!s->pop(value) || value != 3) {
        delete s;
        return false;
    }
    if (!s->pop(value) || value != 2) {
        delete s;
        return false;
    }
    if (!s->pop(value) || value != 1) {
        delete s;
        return false;
    }
    if (s->pop(value)) { // should be empty
        delete s;
        return false;
    }

    if (s->size() != 0) {
        delete s;
        return false;
    }
    if (!s->isEmpty()) {
        delete s;
        return false;
    }

    if (!s->push(1)) {
        delete s;
        return false;
    }
    if (!s->push(2)) {
        delete s;
        return false;
    }
    if (!s->push(3)) {
        delete s;
        return false;
    }

    s->clear();

    if (s->size() != 0) {
        delete s;
        return false;
    }
    if (!s->isEmpty()) {
        delete s;
        return false;
    }

    if (s->pop(value)) { // should be empty
        delete s;
        return false;
    }

    delete s;

    return true;
}

bool test_DynamicStack4() {
    // test DynamicStack through Stack interface with std::string

    Stack<std::string>* s = new DynamicStack<std::string>(3);

    if (!s->isEmpty()) {
        delete s;
        return false;
    }
    if (s->size() != 0) {
        delete s;
        return false;
    }

    if (!s->push("1")) {
        delete s;
        return false;
    }
    if (!s->push("2")) {
        delete s;
        return false;
    }
    if (!s->push("3")) {
        delete s;
        return false;
    }
    if (!s->push("4")) { // should resize
        delete s;
        return false;
    }
    if (dynamic_cast<DynamicStack<std::string>*>(s)->capacity() <= 3) { // capacity should have increased
        delete s;
        return false;
    }

    std::string value;

    if (!s->peek(value) || value != "4") {
        delete s;
        return false;
    }

    if (!s->pop(value) || value != "4") {
        delete s;
        return false;
    }
    if (!s->pop(value) || value != "3") {
        delete s;
        return false;
    }
    if (!s->pop(value) || value != "2") {
        delete s;
        return false;
    }
    if (!s->pop(value) || value != "1") {
        delete s;
        return false;
    }
    if (s->pop(value)) { // should be empty
        delete s;
        return false;
    }

    if (s->size() != 0) {
        delete s;
        return false;
    }
    if (!s->isEmpty()) {
        delete s;
        return false;
    }

    if (!s->push("1")) {
        delete s;
        return false;
    }
    if (!s->push("2")) {
        delete s;
        return false;
    }
    if (!s->push("3")) {
        delete s;
        return false;
    }

    s->clear();

    if (s->size() != 0) {
        delete s;
        return false;
    }
    if (!s->isEmpty()) {
        delete s;
        return false;
    }

    if (s->pop(value)) { // should be empty
        delete s;
        return false;
    }

    delete s;

    return true;
}

bool test_DynamicStack5() {
    // test copy and move semantics
    int value = 0;
    int value2 = 0;

    DynamicStack<int> s1{3};
    s1.push(1);
    s1.push(2);
    s1.push(3);

    DynamicStack<int> s2(s1);
    if (s1.size() != s2.size()) {
        return false;
    }
    if (s1.isEmpty() != s2.isEmpty()) {
        return false;
    }
    if (!s1.pop(value) || !s2.pop(value2)) {
        return false;
    }
    if (value != value2) {
        return false;
    }
    if (s1.size() != s2.size()) {
        return false;
    }
    if (s1.isEmpty() != s2.isEmpty()) {
        return false;
    }

    DynamicStack<int> s3(std::move(s1));
    if (s1.size() != 0) {
        return false;
    }
    if (!s1.isEmpty()) {
        return false;
    }
    if (s3.size() != 2) {
        return false;
    }
    if (s3.isEmpty()) {
        return false;
    }
    if (!s3.pop(value)) {
        return false;
    }
    if (value != 2) {
        return false;
    }

    DynamicStack<int> s4{3};
    s4.push(4);
    s4.push(5);
    s4.push(6);
    s4 = s3;
    if (s3.size() != s4.size()) {
        return false;
    }
    if (s3.isEmpty() != s4.isEmpty()) {
        return false;
    }
    if (!s3.pop(value) || !s4.pop(value2)) {
        return false;
    }
    if (value != value2) {
        return false;
    }
    if (s3.size() != s4.size()) {
        return false;
    }
    if (s3.isEmpty() != s4.isEmpty()) {
        return false;
    }

    s4.clear();
    s4.push(4);
    s4.push(5);
    s4.push(6);

    DynamicStack<int> s5{3};
    s5.push(7);
    s5.push(8);
    s5.push(9);
    s5 = std::move(s4);
    if (s4.size() != 0) {
        return false;
    }
    if (!s4.isEmpty()) {
        return false;
    }
    if (s5.size() != 3) {
        return false;
    }
    if (s5.isEmpty()) {
        return false;
    }
    if (!s5.pop(value)) {
        return false;
    }
    if (value != 6) {
        return false;
    }

    return true;
}

bool test_DynamicStack6() {
    // test copy semantics through Stack interface
    // there are no move semantics to test here
    // (move is just moving the pointer to a Stack object)
    int value = 0;
    int value2 = 0;

    Stack<int>* s1 = new DynamicStack<int>(3);
    s1->push(1);
    s1->push(2);
    s1->push(3);

    Stack<int>* s2 = s1->clone();
    if (s1->size() != s2->size()) {
        delete s1;
        delete s2;
        return false;
    }
    if (s1->isEmpty() != s2->isEmpty()) {
        delete s1;
        delete s2;
        return false;
    }
    if (!s1->pop(value) || !s2->pop(value2)) {
        delete s1;
        delete s2;
        return false;
    }
    if (value != value2) {
        delete s1;
        delete s2;
        return false;
    }
    if (s1->size() != s2->size()) {
        delete s1;
        delete s2;
        return false;
    }
    if (s1->isEmpty() != s2->isEmpty()) {
        delete s1;
        delete s2;
        return false;
    }

    delete s1;
    delete s2;

    return true;
}

// NOLINTEND(bugprone-use-after-move,hicpp-invalid-access-moved,clang-analyzer-cplusplus.Move)
