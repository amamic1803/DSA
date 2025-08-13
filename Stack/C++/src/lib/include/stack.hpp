#ifndef STACK_HPP
#define STACK_HPP


#include <algorithm>
#include <cstdlib>
#include <new>
#include <utility>


template <typename T>
class Stack {
private:
    int _size = 0;
public:
    // empty constructor
    Stack() = default;

    // copy constructor
    Stack(const Stack& other) = default;

    // move constructor
    Stack(Stack&& other) noexcept : _size(other._size) {
        other._size = 0;
    }

    // copy assignment operator
    Stack& operator=(const Stack& other) {
        if (this == &other) {
            return *this;
        }
        _size = other._size;
        return *this;
    }

    // move assignment operator
    Stack& operator=(Stack&& other) noexcept {
        if (this == &other) {
            return *this;
        }
        _size = other._size;
        other._size = 0;
        return *this;
    }

    // destructor
    virtual ~Stack() = default;

    /**
     * Clone the stack.
     * @return A pointer to the cloned stack.
     */
    [[nodiscard]] virtual Stack* clone() const = 0;

    /**
     * Add an element to the top of the stack.
     * @param value Element to add.
     * @return true if the element is added successfully, false otherwise.
     */
    virtual bool push(T value) = 0;

    /**
     * Remove the top element of the stack.
     * @param value Reference to store the top element.
     * @return true if the stack is not empty, false otherwise.
     */
    virtual bool pop(T& value) = 0;

    /**
     * Get the top element of the stack without removing it.
     * @param value Reference to store the top element.
     * @return true if the stack is not empty, false otherwise.
     */
    virtual bool peek(T& value) const = 0;

    /**
     * Remove all elements from the stack.
     */
    virtual void clear() = 0;

    /**
     * Get the size of the stack.
     * @return The size of the stack.
     */
    [[nodiscard]] int size() const { return _size; }

    /**
     * Check if the stack is empty.
     * @return true if the stack is empty, false otherwise.
     */
    [[nodiscard]] bool isEmpty() const { return _size == 0; }
protected:
    void setSize(const int size) {
        _size = size;
    }
};

template <typename T>
class ListStack : public Stack<T> {
private:
    // NOLINTBEGIN(misc-non-private-member-variables-in-classes)
    struct Node {
        T data;
        Node* next;
        Node() = default;
        Node(T value, Node* next) : data(std::move(value)), next(next) {}
    };
    // NOLINTEND(misc-non-private-member-variables-in-classes)
    Node* top = nullptr;
public:
    ListStack() = default;

    // Copy constructor
    ListStack(const ListStack& other) : Stack<T>(other), top(other.top) {
        Node** current = &(top);
        while (*current != nullptr) {
            Node* new_node = new Node((*current)->data, (*current)->next);
            *current = new_node;
            current = &((*current)->next);
        }
    }

    // Move constructor
    // NOLINTBEGIN(bugprone-use-after-move, hicpp-invalid-access-moved)
    ListStack(ListStack&& other) noexcept : Stack<T>(std::move(other)), top(other.top) {
        other.top = nullptr;
    }
    // NOLINTEND(bugprone-use-after-move, hicpp-invalid-access-moved)

    // Copy assignment operator
    ListStack& operator=(const ListStack& other) {
        if (this == &other) {
            return *this;
        }
        this->clear();
        Stack<T>::operator=(other);
        top = other.top;
        Node** current = &(top);
        while (*current != nullptr) {
            Node* new_node = new Node((*current)->data, (*current)->next);
            *current = new_node;
            current = &((*current)->next);
        }
        return *this;
    }

    // Move assignment operator
    ListStack& operator=(ListStack&& other) noexcept {
        if (this == &other) {
            return *this;
        }
        this->clear();
        top = other.top;
        other.top = nullptr;
        Stack<T>::operator=(std::move(other));
        return *this;
    }

    ~ListStack() override {
        this->ListStack<T>::clear();
    }

    [[nodiscard]] Stack<T>* clone() const override {
        return new ListStack(*this);
    }

    bool push(T value) override {
        Node* new_node = new (std::nothrow) Node(value, top);
        if (new_node == nullptr) {
            return false;
        }
        top = new_node;
        this->setSize(this->size() + 1);
        return true;
    }

    bool pop(T& value) override {
        Node* top_node = top;
        if (top_node == nullptr) {
            return false;
        }
        top = top_node->next;
        value = std::move(top_node->data);
        delete top_node;
        this->setSize(this->size() - 1);
        return true;
    }

    bool peek(T& value) const override {
        if (top == nullptr) {
            return false;
        }
        value = top->data;
        return true;
    }

    void clear() override {
        T value;
        // NOLINTNEXTLINE(clang-analyzer-optin.cplusplus.VirtualCall)
        while (pop(value)) {}
    }
};

template <typename T>
class StaticStack : public Stack<T> {
private:
    int _capacity;
    T* data;
    int top = -1;
public:
    explicit StaticStack(const int capacity) : Stack<T>(), _capacity(capacity), data(new T[_capacity]) {}

    StaticStack(const StaticStack& other) : Stack<T>(other), _capacity(other._capacity), data(new T[_capacity]), top(other.top) {
        std::copy(other.data, other.data + this->size(), data);
    }

    // NOLINTBEGIN(bugprone-use-after-move, hicpp-invalid-access-moved)
    StaticStack(StaticStack&& other) noexcept : Stack<T>(std::move(other)), _capacity(other._capacity), data(other.data), top(other.top) {
        other._capacity = 0;
        other.data = nullptr;
        other.top = -1;
    }
    // NOLINTEND(bugprone-use-after-move, hicpp-invalid-access-moved)

    StaticStack& operator=(const StaticStack& other) {
        if (this == &other) {
            return *this;
        }
        Stack<T>::operator =(other);
        _capacity = other._capacity;
        top = other.top;
        delete[] data;
        data = new T[_capacity];
        std::copy(other.data, other.data + this->size(), data);
        return *this;
    }

    StaticStack& operator=(StaticStack&& other) noexcept {
        if (this == &other) {
            return *this;
        }
        _capacity = other._capacity;
        other._capacity = 0;
        top = other.top;
        other.top = -1;
        delete[] data;
        data = other.data;
        other.data = nullptr;
        Stack<T>::operator =(std::move(other));
        return *this;
    }

    ~StaticStack() override { delete[] data; }

    [[nodiscard]] Stack<T>* clone() const override {
        return new StaticStack(*this);
    }

    /**
     * Get the capacity of the stack.
     * @return The capacity of the stack.
     */
    [[nodiscard]] int capacity() const { return _capacity; }

    /**
     * Check if the stack is full.
     * @return true if the stack is full, false otherwise.
     */
    [[nodiscard]] bool isFull() const { return top + 1 >= _capacity; }

    bool push(T value) override {
        if (top + 1 < _capacity) {
            data[++top] = value;
            this->setSize(this->size() + 1);
            return true;
        }
        return false;
    }

    bool pop(T& value) override {
        if (top != -1) {
            value = data[top--];
            this->setSize(this->size() - 1);
            return true;
        }
        return false;
    }

    bool peek(T& value) const override {
        if (top != -1) {
            value = data[top];
            return true;
        }
        return false;
    }

    void clear() override {
        top = -1;
        this->setSize(0);
    }
};

template <typename T>
class DynamicStack : public Stack<T> {
private:
    int _capacity;
    T* data;
    int top = -1;
public:
    DynamicStack() : Stack<T>(), _capacity(4), data(new T[_capacity]) {}

    explicit DynamicStack(const int capacity) : Stack<T>(), _capacity(capacity) {
        if (_capacity < 4) {
            this->_capacity = 4;
        }
        data = new T[_capacity];
    }

    DynamicStack(const DynamicStack& other) : Stack<T>(other), _capacity(other._capacity), data(new T[_capacity]), top(other.top) {
        std::copy(other.data, other.data + this->size(), data);
    }

    // NOLINTBEGIN(bugprone-use-after-move, hicpp-invalid-access-moved)
    DynamicStack(DynamicStack&& other) noexcept : Stack<T>(std::move(other)), _capacity(other._capacity), data(other.data), top(other.top) {
        other._capacity = 0;
        other.data = nullptr;
        other.top = -1;
    }
    // NOLINTEND(bugprone-use-after-move, hicpp-invalid-access-moved)

    DynamicStack& operator=(const DynamicStack& other) {
        if (this == &other) {
            return *this;
        }
        Stack<T>::operator=(other);
        _capacity = other._capacity;
        delete[] data;
        data = new T[_capacity];
        std::copy(other.data, other.data + this->size(), data);
        top = other.top;
        return *this;
    }

    DynamicStack& operator=(DynamicStack&& other) noexcept {
        if (this == &other) {
            return *this;
        }
        _capacity = other._capacity;
        other._capacity = 0;
        delete[] data;
        data = other.data;
        other.data = nullptr;
        top = other.top;
        other.top = -1;
        Stack<T>::operator =(std::move(other));
        return *this;
    }

    ~DynamicStack() override { delete[] data; }

    [[nodiscard]] Stack<T>* clone() const override {
        return new DynamicStack(*this);
    }

    /**
     * Get the current capacity of the stack.
     * @return The current capacity of the stack.
     */
    [[nodiscard]] int capacity() const { return _capacity; }

    bool push(T value) override {
        if (top + 1 >= _capacity) {
            _capacity = std::max(_capacity * 2, 4);
            T* new_data = new (std::nothrow) T[_capacity];
            if (new_data == nullptr) {
                return false;
            }
            std::copy(data, data + this->size(), new_data);
            delete[] data;
            data = new_data;
        }
        data[++top] = value;
        this->setSize(this->size() + 1);
        return true;
    }

    bool pop(T& value) override {
        if (top != -1) {
            value = data[top--];
            this->setSize(this->size() - 1);
            return true;
        }
        return false;
    }

    bool peek(T& value) const override {
        if (top != -1) {
            value = data[top];
            return true;
        }
        return false;
    }

    void clear() override {
        top = -1;
        this->setSize(0);
    }
};


#endif // STACK_HPP
