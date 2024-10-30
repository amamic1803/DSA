#ifndef STACK_LIB_HPP
#define STACK_LIB_HPP

#include <cstdlib>
#include <new>

template <typename T>
class Stack {
protected:
    int _size = 0;
public:
    Stack() = default;
    virtual ~Stack() = default;

    /**
     * Add a new element to the top of the stack
     * @param value new element to add
     * @return true if the element is added successfully, false otherwise
     */
    virtual bool push(T value) = 0;

    /**
     * Remove the top element of the stack
     * @param value reference to store the top element
     * @return true if the stack is not empty, false otherwise
     */
    virtual bool pop(T& value) = 0;

    /**
     * Get the top element of the stack without removing it
     * @param value reference to store the top element
     * @return true if the stack is not empty, false otherwise
     */
    virtual bool peek(T& value) = 0;

    /**
     * Clear the stack
     */
    void clear() {
        T value;
        while (pop(value));
    }

    /**
     * Get the size of the stack
     * @return size of the stack
     */
    [[nodiscard]] int size() const { return _size; }

    /**
     * Check if the stack is empty
     * @return true if the stack is empty, false otherwise
     */
    [[nodiscard]] bool isEmpty() const { return _size == 0; }
};

template <typename T>
class ListStack : public Stack<T> {
private:
    struct Node {
        T data;
        Node* next;
        Node() = default;
        Node(T value, Node* next) : data(value), next(next) {}
    };
    Node* top = nullptr;
public:
    ListStack() = default;
    ~ListStack() override {
        this->clear();
    }
    bool push(T value) override {
        Node* new_node = new (std::nothrow) Node(value, top);
        if (new_node == nullptr)
            return false;
        top = new_node;
        this->_size++;
        return true;
    }
    bool pop(T& value) override {
        Node* top_node = top;
        if (top_node == nullptr)
            return false;
        top = top_node->next;
        value = top_node->data;
        delete top_node;
        this->_size--;
        return true;
    }
    bool peek(T& value) override {
        Node* top_node = top;
        if (top_node == nullptr)
            return false;
        value = top_node->data;
        return true;
    }
};

template <typename T>
class StaticStack : public Stack<T> {
private:
    int capacity;
    T data[] = new T[capacity];
    int top = -1;
public:
    explicit StaticStack(const int capacity) : capacity(capacity) {}

    ~StaticStack() override {
        delete[] data;
    }

    bool push(T value) override {
        if (top + 1 < capacity) {
            data[top] = value;
            top++;
            this->_size++;
            return true;
        }
        return false;
    }

    bool pop(T& value) override {
        if (top != -1) {
            value = data[top--];
            this->_size--;
            return true;
        }
        return false;
    }

    bool peek(T& value) override {
        if (top != -1)
            value = data[top];
        return top != -1;
    }
};

template <typename T>
class DynamicStack : public Stack<T> {
private:
    int _capacity;
    T* data;
    int top;
public:
    DynamicStack() : _capacity(4), data(new T[_capacity]), top(-1) {
        if (this->data == nullptr)
            throw std::bad_alloc();
    }
    explicit DynamicStack(const int capacity) : _capacity(capacity), top(-1) {
        if (_capacity < 4)
            this->_capacity = 4;
        this->data = new T[_capacity];
        if (this->data == nullptr)
            throw std::bad_alloc();
    }
    ~DynamicStack() override {
        free(data);
    }

    [[nodiscard]] int capacity() const { return _capacity; }

    bool push(T value) override {
        if (top + 1 >= _capacity) {
            _capacity *= 2;
            T* new_data = realloc(data, sizeof(T) * _capacity);
            if (new_data == nullptr)
                return false;
            this->data = new_data;
        }

        data[top] = value;
        top++;
        this->_size++;
        return true;
    }

    bool pop(T& value) override {
        if (top != -1) {
            value = data[top--];
            this->_size--;
            return true;
        }
        return false;
    }

    bool peek(T& value) override {
        if (top != -1) {
            value = data[top];
        }
        return top != -1;
    }
};


#endif // STACK_LIB_HPP
