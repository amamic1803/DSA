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
    LinkedList() = default;

    // destructor
    virtual ~LinkedList() = default;

    /**
     * @brief Returns a copy of this LinkedList instance.
     * @return a copy of this LinkedList instance
     */
    [[nodiscard]] virtual LinkedList* clone() const = 0;

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
    SinglyLinkedList(const SinglyLinkedList& other) : LinkedList<T>() {
        this->_size = other._size;
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
    SinglyLinkedList(SinglyLinkedList&& other) noexcept : LinkedList<T>(), head(other.head) {
        this->_size = other._size;
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
    ~SinglyLinkedList() override { this->clear(); }

    [[nodiscard]] SinglyLinkedList* clone() const override {
        return new SinglyLinkedList(*this);
    }

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
    [[nodiscard]] Iterator begin() const { return Iterator(head); }
    [[nodiscard]] Iterator end() const { return Iterator(nullptr); }
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
    DoublyLinkedList(const DoublyLinkedList& other) : LinkedList<T>() {
        this->_size = other._size;
        Node** p = &head;
        for (T value : other) {
            *p = new Node(value);
            p = &((*p)->next);
        }
    }

    // copy assignment
    DoublyLinkedList& operator=(const DoublyLinkedList& other) {
        if (this != &other) {
            this->clear();
            this->_size = other._size;
            Node** p = &head;
            for (T value : other) {
                *p = new Node(value);
                p = &((*p)->next);
            }
        }
        return *this;
    }

    // move constructor
    DoublyLinkedList(DoublyLinkedList&& other) noexcept : LinkedList<T>(), head(other.head), tail(other.tail) {
        this->_size = other._size;
        other.head = other.tail = nullptr;
        other._size = 0;
    }

    // move assignment
    DoublyLinkedList& operator=(DoublyLinkedList&& other) noexcept {
        if (this != &other) {
            this->clear();
            head = other.head;
            tail = other.tail;
            this->_size = other._size;
            other.head = other.tail = nullptr;
            other._size = 0;
        }
        return *this;
    }

    // destructor
    ~DoublyLinkedList() override { this->clear(); }

    [[nodiscard]] DoublyLinkedList* clone() const override {
        return new DoublyLinkedList(*this);
    }

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
        } else if (index == 0) {
            // insert at the beginning
            Node* new_node = new Node(value, nullptr, head);
            head->prev = new_node;
            head = new_node;
        } else if (index == this->_size) {
            // insert at the end
            Node* new_node = new Node(value, tail, nullptr);
            tail->next = new_node;
            tail = new_node;
        } else if (index <= this->_size >> 1) {
            // insert from the head
            Node* current = head;
            for (int i = 1; i < index; i++)
                current = current->next;
            Node* new_node = new Node(value, current, current->next);
            new_node->prev->next = new_node;
            if (new_node->next != nullptr)
                new_node->next->prev = new_node;
        } else {
            // insert from the tail
            Node* current = tail;
            for (int i = this->_size - 1; i > index; i--)
                current = current->prev;
            Node* new_node = new Node(value, current->prev, current);
            new_node->next->prev = new_node;
            if (new_node->prev != nullptr)
                new_node->prev->next = new_node;
        }

        this->_size++;
    }

    T erase(int index) override {
        if (index < 0 || index >= this->_size)
            throw std::out_of_range("Index out of bounds");

        T value;
        if (this->_size == 1) {
            value = head->data;
            delete head;
            head = tail = nullptr;
        } else if (index == 0) {
            // remove from the beginning
            Node* temp = head;
            value = temp->data;
            temp->next->prev = nullptr;
            head = temp->next;
            delete temp;
        } else if (index == this->_size - 1) {
            // remove from the end
            Node* temp = tail;
            value = temp->data;
            temp->prev->next = nullptr;
            tail = temp->prev;
            delete temp;
        } else if (index <= this->_size >> 1) {
            // remove from the head
            Node* current = head;
            for (int i = 0; i < index; i++)
                current = current->next;
            Node* temp = current;
            value = temp->data;
            temp->prev->next = temp->next;
            if (temp->next != nullptr)
                temp->next->prev = temp->prev;
            delete temp;
        } else {
            // remove from the tail
            Node* current = tail;
            for (int i = this->_size - 1; i > index; i--)
                current = current->prev;
            Node* temp = current;
            value = temp->data;
            temp->next->prev = temp->prev;
            if (temp->prev != nullptr)
                temp->prev->next = temp->next;
            delete temp;
        }

        this->_size--;

        return value;
    }

    bool remove(const T& value) override {
        Node* current = head;

        while (current != nullptr) {
            if (current->data == value) {
                if (current->prev != nullptr)
                    current->prev->next = current->next;
                if (current->next != nullptr)
                    current->next->prev = current->prev;
                if (current == head)
                    head = current->next;
                if (current == tail)
                    tail = current->prev;
                delete current;
                this->_size--;
                return true;
            }
            current = current->next;
        }

        return false;
    }

    int remove_all(const T& value) override {
        int removed = 0;
        Node* current = head;

        while (current != nullptr) {
            if (current->data == value) {
                if (current->prev != nullptr)
                    current->prev->next = current->next;
                if (current->next != nullptr)
                    current->next->prev = current->prev;
                if (current == head)
                    head = current->next;
                if (current == tail)
                    tail = current->prev;
                Node* temp = current;
                current = current->next;
                delete temp;
                this->_size--;
                removed++;
            } else {
                current = current->next;
            }
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
    [[nodiscard]] Iterator begin() const { return Iterator(head); }
    [[nodiscard]] Iterator end() const { return Iterator(nullptr); }
};

#endif // LINKED_LIST_HPP
