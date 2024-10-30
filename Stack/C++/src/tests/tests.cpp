#include "stack.hpp"
#include "tests.hpp"
#include <algorithm>
#include <stdexcept>
#include <string>
#include <vector>

int main(const int argc, char *argv[]) {
    if (argc != 2) {
        return -2;
    }

    int problem_number;
    try {
        problem_number = std::stoi(argv[1]);
    } catch (std::invalid_argument &_) {
        return -3;
    } catch (std::out_of_range &_) {
        return -4;
    } catch (...) {
        return -5;
    }

    bool test_result;
    switch (problem_number) {
        case 1:
            test_result = test_p0001();
            break;
        default:
            return -6;
    }

    return test_result ? 0 : -1;
}

bool test_p0001() {
    Stack<int>* p = new ListStack<int>();
    return false;
}