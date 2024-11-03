#include "queue.hpp"
#include "tests.hpp"
#include <string>
#include <utility>

int main(const int argc, char *argv[]) {
    if (argc != 2) {
        return -2;
    }

    const std::string arg{argv[1]};

    bool test_result;
    if (arg == "ListQueue1")
        test_result = test_ListQueue1();
    else if (arg == "ListQueue2")
        test_result = test_ListQueue2();
    else if (arg == "ListQueue3")
        test_result = test_ListQueue3();
    else if (arg == "ListQueue4")
        test_result = test_ListQueue4();
    else if (arg == "ListQueue5")
        test_result = test_ListQueue5();
    else if (arg == "StaticQueue1")
        test_result = test_StaticQueue1();
    else if (arg == "StaticQueue2")
        test_result = test_StaticQueue2();
    else if (arg == "StaticQueue3")
        test_result = test_StaticQueue3();
    else if (arg == "StaticQueue4")
        test_result = test_StaticQueue4();
    else if (arg == "StaticQueue5")
        test_result = test_StaticQueue5();
    else if (arg == "DynamicQueue1")
        test_result = test_DynamicQueue1();
    else if (arg == "DynamicQueue2")
        test_result = test_DynamicQueue2();
    else if (arg == "DynamicQueue3")
        test_result = test_DynamicQueue3();
    else if (arg == "DynamicQueue4")
        test_result = test_DynamicQueue4();
    else if (arg == "DynamicQueue5")
        test_result = test_DynamicQueue5();
    else
        return -3;

    return test_result ? 0 : -1;
}

bool test_ListQueue1() {
    // Test basic enqueue and dequeue operations
    ListQueue<int> queue;
    if (!queue.enqueue(1))
        return false;
    if (!queue.enqueue(2))
        return false;
    int value;
    if (!queue.dequeue(value) || value != 1)
        return false;
    if (!queue.dequeue(value) || value != 2)
        return false;
    if (queue.dequeue(value))
        return false; // Queue should be empty
    return true;
}
bool test_ListQueue2() {
    // Test copy constructor and assignment operator
    ListQueue<int> queue1;
    if (!queue1.enqueue(1))
        return false;
    if (!queue1.enqueue(2))
        return false;
    ListQueue<int> queue2(queue1); // Copy constructor
    int value;
    if (!queue2.dequeue(value) || value != 1)
        return false;
    if (!queue2.dequeue(value) || value != 2)
        return false;
    ListQueue<int> queue3;
    queue3 = queue1; // Copy assignment
    if (!queue3.dequeue(value) || value != 1)
        return false;
    if (!queue3.dequeue(value) || value != 2)
        return false;
    return true;
}
bool test_ListQueue3() {
    // Test move constructor and assignment operator
    ListQueue<int> queue1;
    if (!queue1.enqueue(1))
        return false;
    if (!queue1.enqueue(2))
        return false;
    ListQueue<int> queue2(std::move(queue1)); // Move constructor
    int value;
    if (!queue2.dequeue(value) || value != 1)
        return false;
    if (!queue2.dequeue(value) || value != 2)
        return false;
    queue2.enqueue(3);
    queue2.enqueue(4);
    ListQueue<int> queue3;
    queue3 = std::move(queue2); // Move assignment
    if (!queue3.dequeue(value) || value != 3)
        return false;
    if (!queue3.dequeue(value) || value != 4)
        return false;
    return true;
}
bool test_ListQueue4() {
    // Test handling through pointer to abstract base class
    Queue<int>* queue = new ListQueue<int>();
    if (!queue->enqueue(1))
        return false;
    if (!queue->enqueue(2))
        return false;
    int value;
    if (!queue->dequeue(value) || value != 1)
        return false;
    if (!queue->dequeue(value) || value != 2)
        return false;
    delete queue;
    return true;
}
bool test_ListQueue5() {
    // Test clone method
    ListQueue<int> queue1;
    if (!queue1.enqueue(1))
        return false;
    if (!queue1.enqueue(2))
        return false;
    Queue<int>* queue2 = queue1.clone();
    int value;
    if (!queue2->dequeue(value) || value != 1)
        return false;
    if (!queue2->dequeue(value) || value != 2)
        return false;
    delete queue2;
    return true;
}
bool test_StaticQueue1() {
    // Test basic enqueue and dequeue operations
    StaticQueue<int> queue(3);
    if (!queue.enqueue(1))
        return false;
    if (!queue.enqueue(2))
        return false;
    int value;
    if (!queue.dequeue(value) || value != 1)
        return false;
    if (!queue.dequeue(value) || value != 2)
        return false;
    if (queue.dequeue(value))
        return false; // Queue should be empty
    return true;
}
bool test_StaticQueue2() {
    // Test copy constructor and assignment operator
    StaticQueue<int> queue1(3);
    if (!queue1.enqueue(1))
        return false;
    if (!queue1.enqueue(2))
        return false;
    StaticQueue<int> queue2(queue1); // Copy constructor
    int value;
    if (!queue2.dequeue(value) || value != 1)
        return false;
    if (!queue2.dequeue(value) || value != 2)
        return false;
    StaticQueue<int> queue3(3);
    queue3 = queue1; // Copy assignment
    if (!queue3.dequeue(value) || value != 1)
        return false;
    if (!queue3.dequeue(value) || value != 2)
        return false;
    return true;
}
bool test_StaticQueue3() {
    // Test move constructor and assignment operator
    StaticQueue<int> queue1(3);
    if (!queue1.enqueue(1))
        return false;
    if (!queue1.enqueue(2))
        return false;
    StaticQueue<int> queue2(std::move(queue1)); // Move constructor
    int value;
    if (!queue2.dequeue(value) || value != 1)
        return false;
    if (!queue2.dequeue(value) || value != 2)
        return false;
    queue2.enqueue(3);
    queue2.enqueue(4);
    StaticQueue<int> queue3(3);
    queue3 = std::move(queue2); // Move assignment
    if (!queue3.dequeue(value) || value != 3)
        return false;
    if (!queue3.dequeue(value) || value != 4)
        return false;
    return true;
}
bool test_StaticQueue4() {
    // Test handling through pointer to abstract base class
    Queue<int>* queue = new StaticQueue<int>(3);
    if (!queue->enqueue(1))
        return false;
    if (!queue->enqueue(2))
        return false;
    int value;
    if (!queue->dequeue(value) || value != 1)
        return false;
    if (!queue->dequeue(value) || value != 2)
        return false;
    delete queue;
    return true;
}
bool test_StaticQueue5() {
    // Test clone method
    StaticQueue<int> queue1(3);
    if (!queue1.enqueue(1))
        return false;
    if (!queue1.enqueue(2))
        return false;
    Queue<int>* queue2 = queue1.clone();
    int value;
    if (!queue2->dequeue(value) || value != 1)
        return false;
    if (!queue2->dequeue(value) || value != 2)
        return false;
    delete queue2;
    return true;
}
bool test_DynamicQueue1() {
    // Test basic enqueue and dequeue operations
    DynamicQueue<int> queue(3);
    if (!queue.enqueue(1))
        return false;
    if (!queue.enqueue(2))
        return false;
    int value;
    if (!queue.dequeue(value) || value != 1)
        return false;
    if (!queue.dequeue(value) || value != 2)
        return false;
    if (queue.dequeue(value))
        return false; // Queue should be empty
    return true;
}
bool test_DynamicQueue2() {
    // Test copy constructor and assignment operator
    DynamicQueue<int> queue1(3);
    if (!queue1.enqueue(1))
        return false;
    if (!queue1.enqueue(2))
        return false;
    DynamicQueue<int> queue2(queue1); // Copy constructor
    int value;
    if (!queue2.dequeue(value) || value != 1)
        return false;
    if (!queue2.dequeue(value) || value != 2)
        return false;
    DynamicQueue<int> queue3(3);
    queue3 = queue1; // Copy assignment
    if (!queue3.dequeue(value) || value != 1)
        return false;
    if (!queue3.dequeue(value) || value != 2)
        return false;
    return true;
}
bool test_DynamicQueue3() {
    // Test move constructor and assignment operator
    DynamicQueue<int> queue1(3);
    if (!queue1.enqueue(1))
        return false;
    if (!queue1.enqueue(2))
        return false;
    DynamicQueue<int> queue2(std::move(queue1)); // Move constructor
    int value;
    if (!queue2.dequeue(value) || value != 1)
        return false;
    if (!queue2.dequeue(value) || value != 2)
        return false;
    queue2.enqueue(3);
    queue2.enqueue(4);
    DynamicQueue<int> queue3(3);
    queue3 = std::move(queue2); // Move assignment
    if (!queue3.dequeue(value) || value != 3)
        return false;
    if (!queue3.dequeue(value) || value != 4)
        return false;
    return true;
}
bool test_DynamicQueue4() {
    // Test handling through pointer to abstract base class
    Queue<int>* queue = new DynamicQueue<int>(3);
    if (!queue->enqueue(1))
        return false;
    if (!queue->enqueue(2))
        return false;
    int value;
    if (!queue->dequeue(value) || value != 1)
        return false;
    if (!queue->dequeue(value) || value != 2)
        return false;
    delete queue;
    return true;
}
bool test_DynamicQueue5() {
    // Test clone method
    DynamicQueue<int> queue1(3);
    if (!queue1.enqueue(1))
        return false;
    if (!queue1.enqueue(2))
        return false;
    Queue<int>* queue2 = queue1.clone();
    int value;
    if (!queue2->dequeue(value) || value != 1)
        return false;
    if (!queue2->dequeue(value) || value != 2)
        return false;
    delete queue2;
    return true;
}
