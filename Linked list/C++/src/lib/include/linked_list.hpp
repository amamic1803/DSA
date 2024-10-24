#ifndef LINKED_LIST_HPP
#define LINKED_LIST_HPP

template <typename T> class LinkedList {
public:
    LinkedList() = default;
    LinkedList(const LinkedList& other);
    LinkedList& operator=(const LinkedList& other) = delete;
    LinkedList(LinkedList&& other) noexcept = default;
    LinkedList& operator=(LinkedList&& other) noexcept = default;
    virtual ~LinkedList() = default;
    virtual bool push_front(T value) = 0;
    virtual bool push_back(T value) = 0;
    virtual T pop_front() = 0;
    virtual T pop_back() = 0;
};

template <typename T> class SinglyLinkedList : public LinkedList<T> {
private:
    struct Node {
        T data;
        Node* next = nullptr;
        Node() = default;
        explicit Node(T value) : data(value) {}
    };

    Node* head = nullptr;
    Node* tail = nullptr;
    int size = 0;
public:
    SinglyLinkedList() = default;
    ~SinglyLinkedList() override {
        while (head != nullptr) {
            const Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

template <typename T> class DoublyLinkedList : public LinkedList<T> {
private:
    struct Node {
        T data;
        Node* prev;
        Node* next;
        Node() : data(), prev(nullptr), next(nullptr) {}
        explicit Node(T value) : data(value), prev(nullptr), next(nullptr) {}
    };
    Node* head = nullptr;
    Node* tail = nullptr;
    int size = 0;
public:
    DoublyLinkedList() = default;
};

#endif // LINKED_LIST_HPP
