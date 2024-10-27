#ifndef LINKED_LIST_HPP
#define LINKED_LIST_HPP

#include <iostream>
#include <stdexcept>

template <typename T>
class LinkedList {
protected:
    int _size = 0;
public:
    // constructors
    LinkedList() noexcept = default ;
    explicit LinkedList(int size) noexcept : _size(size) {}

    // destructor
    virtual ~LinkedList() { clear(); }

    // copy constructor
    LinkedList(const LinkedList& other) = default;
    // copy assignment
    LinkedList& operator=(const LinkedList& other) = default;

    // move constructor
    LinkedList(LinkedList&& other) noexcept = default;
    // move assignment
    LinkedList& operator=(LinkedList&& other) noexcept = default;

    /**
     * @brief Returns the number of elements in this list.
     * @return the number of elements in this list
     */
    [[nodiscard]] int size() const { return _size; }

    /**
     * @brief Returns true if this list contains no elements.
     * @return true if this list contains no elements
     */
    [[nodiscard]] bool empty() const { return _size == 0; }

    /**
     * @brief Removes all elements from this list.
     */
    void clear() {
        while (!empty())
            pop_front();
    }

    /**
     * @brief Returns the first element in this list.
     * @return the first element in this list
     */
    [[nodiscard]] T& front() const { return get(0); }

    /**
     * @brief Returns the last element in this list.
     * @return the last element in this list
     */
    [[nodiscard]] T& back() const { return get(_size - 1); }

    /**
     * @brief Returns the element at the specified position in this list.
     * @param index index of the element to return
     * @return true if the element was retrieved successfully
     */
    [[nodiscard]] virtual T& get(int index) const = 0;

    /**
     * @brief Inserts the specified element at the beginning of this list.
     * @param value the element to add
     * @return true if the element was added successfully
     */
    void push_front(T value) { insert(0, value); }

    /**
     * @brief Appends the specified element to the end of this list.
     * @param value the element to add
     * @return true if the element was added successfully
     */
    void push_back(T value) { insert(_size, value); }

    /**
     * @brief Inserts the specified element at the specified position in this list.
     * @param index index at which the specified element is to be inserted
     * @param value element to be inserted
     * @return true if the element was inserted successfully
     */
    virtual void insert(int index, T value) = 0;

    /**
     * @brief Removes and returns the first element from this list.
     * @return the first element from this list
     */
    T pop_front() { return erase(0); }

    /**
     * @brief Removes and returns the last element from this list.
     * @return the last element from this list
     */
    T pop_back() { return erase(_size - 1); }

    /**
     * @brief Removes the element at the specified position in this list.
     * @param index the index of the element to be removed
     * @return the element previously at the specified position
     */
    virtual T erase(int index) = 0;

    /**
     * @brief Removes the first occurrence of the specified element from this list, if it is present.
     * @param value element to be removed from this list, if present
     * @return true if this list contained the specified element
     */
    virtual bool remove(const T& value) = 0;

    /**
     * @brief Removes all occurrences of the specified element from this list, if it is present.
     * @param value element to be removed from this list, if present
     * @return the number of elements removed
     */
    virtual int remove_all(const T& value) = 0;

    /**
     * @brief Returns the index of the first occurrence of the specified element in this list, or -1 if this list does not contain the element.
     * @param value element to search for
     * @return the index of the first occurrence of the specified element in this list, or -1 if this list does not contain the element
     */
    [[nodiscard]] int position(const T& value) const {
        int index = 0;
        for (T element : *this) {
            if (element == value)
                return index;
            index++;
        }
        return -1;
    };

    /**
     * @brief Prints the elements of this list to the standard output stream.
     */
    void print() const {
        std::cout << '[';
        bool first = true;
        for (T value : *this) {
            if (first) {
                std::cout << value;
                first = false;
            } else {
                std::cout << value << ", ";
            }
        }
        std::cout << "]\n";
    }
};

template <typename T>
class SinglyLinkedList : public LinkedList<T> {
private:
    struct Node {
        T data;
        Node* next = nullptr;
        Node() = default;
        explicit Node(T value) : data(value) {}
        Node(T value, Node* next) : data(value), next(next) {}
    };
    Node* head = nullptr;
public:
    // constructor
    SinglyLinkedList() = default;

    // copy constructor
    SinglyLinkedList(const SinglyLinkedList& other) : LinkedList<T>(other._size) {
        Node** p = &head;
        for (T value : other) {
            *p = new Node(value);
            p = &((*p)->next);
        }
    }

    // copy assignment
    SinglyLinkedList& operator=(const SinglyLinkedList& other) {
        if (this != &other) {
            this->clear();
            Node** p = &head;
            for (T value : other) {
                *p = new Node(value);
                p = &((*p)->next);
            }
            this->_size = other._size;
        }
        return *this;
    }

    // move constructor
    SinglyLinkedList(SinglyLinkedList&& other) noexcept : head(other.head), LinkedList<T>(other._size) {
        other.head = nullptr;
        other._size = 0;
    }

    // move assignment
    SinglyLinkedList& operator=(SinglyLinkedList&& other) noexcept {
        if (this != &other) {
            this->clear();
            head = other.head;
            this->_size = other._size;
            other.head = nullptr;
            other._size = 0;
        }
        return *this;
    }

    // destructor
    ~SinglyLinkedList() override = default;

    [[nodiscard]] T& get(int index) const override {
        if (index < 0 || index >= this->_size)
            throw std::out_of_range("Index out of bounds");
        Node* current = head;
        for (int i = 0; i < index; i++)
            current = current->next;
        return current->data;
    }

    void insert(int index, T value) override {
        if (index < 0 || index > this->_size)
            throw std::out_of_range("Index out of bounds");
        Node** p = &head;
        for (int i = 0; i < index; i++)
            p = &((*p)->next);
        Node *new_node = new Node(value, *p);
        *p = new_node;
        this->_size++;
    }

    T erase(int index) override {
        if (index < 0 || index >= this->_size)
            throw std::out_of_range("Index out of bounds");
        Node** p = &head;
        for (int i = 0; i < index; i++)
            p = &((*p)->next);
        Node* temp = *p;
        *p = temp->next;
        T value = std::move(temp->data);
        delete temp;
        this->_size--;
        return value;
    }

    bool remove(const T& value) override {
        Node** p = &head;
        while ((*p) != nullptr) {
            if ((*p)->data == value) {
                Node* temp = *p;
                *p = temp->next;
                delete temp;
                this->_size--;
                return true;
            }
            p = &((*p)->next);
        }
        return false;
    }

    int remove_all(const T& value) override {
        int removed = 0;
        Node** p = &head;
        while ((*p) != nullptr) {
            if ((*p)->data == value) {
                Node* temp = *p;
                *p = temp->next;
                delete temp;
                this->_size--;
                removed++;
            }
            p = &((*p)->next);
        }
        return removed;
    }

    class Iterator {
    private:
        Node* current;
    public:
        explicit Iterator(Node* node) : current(node) {}

        T& operator*() const { return current->data; }

        Iterator& operator++() {
            current = current->next;
            return *this;
        }

        bool operator!=(const Iterator& other) const {
            return current != other.current;
        }
    };
    Iterator begin() { return Iterator(head); }
    Iterator end() { return Iterator(nullptr); }
};

template <typename T> class DoublyLinkedList : public LinkedList<T> {
private:
    struct Node {
        T data;
        Node* prev = nullptr;
        Node* next = nullptr;
        Node() = default;
        explicit Node(T value) : data(value) {}
        Node(T value, Node* prev, Node* next) : data(value), prev(prev), next(next) {}
    };
    Node* head = nullptr;
    Node* tail = nullptr;
public:
    // constructor
    DoublyLinkedList() = default;

    // copy constructor
    DoublyLinkedList(const DoublyLinkedList& other) : LinkedList<T>(other._size) {}

    // copy assignment
    DoublyLinkedList& operator=(const DoublyLinkedList& other) {}

    // move constructor
    DoublyLinkedList(DoublyLinkedList&& other) noexcept {}

    // move assignment
    DoublyLinkedList& operator=(DoublyLinkedList&& other) noexcept {}

    // destructor
    ~DoublyLinkedList() override = default;

    [[nodiscard]] T& get(int index) const override {
        if (index < 0 || index >= this->_size)
            throw std::out_of_range("Index out of bounds");

        // move from the head
        if (index <= this->_size >> 1) {
            Node* current = head;
            for (int i = 0; i < index; i++)
                current = current->next;
            return current->data;
        }
        // move from the tail
        Node* current = tail;
        for (int i = this->_size - 1; i > index; i--)
            current = current->prev;
        return current->data;
    }

    void insert(int index, T value) override {
        if (index < 0 || index > this->_size)
            throw std::out_of_range("Index out of bounds");

        if (this->_size == 0) {
            head = tail = new Node(value);
        } else if (index <= this->_size >> 1) {
            // insert from the head
            Node* current = head;
            for (int i = 0; i < index; i++)
                current = current->next;
            Node* new_node = new Node(value, current->prev, current);
            // popraviti ako je prev == nullptr
            new_node->prev->next = new_node;
            new_node->next->prev = new_node;
        } else {
            // insert from the tail

        }

        this->_size++;
    }

    T erase(int index) override {
        return true;
    }

    bool remove(T value) override {
        return true;
    }

    int remove_all(T value) override {
        return 0;
    }
};

#endif // LINKED_LIST_HPP
