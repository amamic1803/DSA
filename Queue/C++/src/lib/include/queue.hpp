#ifndef LEETCODE_LIB_HPP
#define LEETCODE_LIB_HPP

#include <algorithm>
#include <new>
#include <utility>

template <typename T>
class Queue {
public:
    Queue() = default;
    Queue(const Queue& other) = delete;
    Queue(Queue&& other) noexcept = delete;
    Queue& operator=(const Queue& other) = delete;
    Queue& operator=(Queue&& other) noexcept = delete;
    virtual ~Queue() = default;

    /**
     * Clones the queue.
     * @return A clone of the queue.
     */
    [[nodiscard]] virtual Queue* clone() const = 0;

    /**
     * Enqueues a value into the queue.
     * @param value The value to enqueue.
     * @return True if the value was enqueued, false otherwise.
     */
    virtual bool enqueue(T value) = 0;

    /**
     * Dequeues a value from the queue.
     * @param value The value to dequeue.
     * @return True if the value was dequeued, false otherwise.
     */
    virtual bool dequeue(T& value) = 0;

    /**
     * Peeks at the value at the front of the queue.
     * @param value The value to peek at.
     * @return True if the value was peeked at, false otherwise.
     */
    virtual bool peek(T& value) const = 0;

    /**
     * Gets the size of the queue.
     * @return The size of the queue.
     */
    [[nodiscard]] virtual int size() const = 0;
};

template <typename T>
class ListQueue : public Queue<T> {
private:
    struct Node {
        T data;
        Node* next;
        Node(T data, Node* next) : data(data), next(next) {}
    };
    int _size = 0;
    Node* read;
    Node* write;
public:
    ListQueue() : read(nullptr), write(nullptr) {}
    ListQueue(const ListQueue& other) : _size(other._size) {
        if (other.read == nullptr) {
            read = write = nullptr;
            return;
        }
        read = new Node(other.read->data, other.read->next);
        Node* current = read;
        while (current->next != nullptr) {
            current->next = new Node(current->next->data, current->next->next);
            current = current->next;
        }
        write = current;
    }
    ListQueue(ListQueue&& other) noexcept : _size(other._size), read(other.read), write(other.write) {
        other._size = 0;
        other.read = other.write = nullptr;
    }
    ListQueue& operator=(const ListQueue& other) {
        if (this == &other)
            return *this;
        _size = other._size;
        if (other.read == nullptr) {
            read = write = nullptr;
            return *this;
        }
        read = new Node(other.read->data, other.read->next);
        Node* current = read;
        while (current->next != nullptr) {
            current->next = new Node(current->next->data, current->next->next);
            current = current->next;
        }
        write = current;
        return *this;
    }
    ListQueue& operator=(ListQueue&& other) noexcept {
        if (this == &other)
            return *this;
        _size = other._size;
        read = other.read;
        write = other.write;
        other._size = 0;
        other.read = other.write = nullptr;
        return *this;
    }
    ~ListQueue() override {
        while (read != nullptr) {
            const Node* temp = read;
            read = read->next;
            delete temp;
        }
    }

    [[nodiscard]] Queue<T>* clone() const override {
        return new ListQueue(*this);
    }

    bool enqueue(T value) override {
        Node* new_node = new (std::nothrow) Node(value, nullptr);
        if (new_node == nullptr)
            return false;
        if (write == nullptr) {
            read = write = new_node;
        } else {
            write->next = new_node;
            write = new_node;
        }
        _size++;
        return true;
    }

    bool dequeue(T& value) override {
        if (read == nullptr)
            return false;
        Node* temp = read;
        value = std::move(temp->data);
        read = temp->next;
        if (read == nullptr)
            write = nullptr;
        delete temp;
        _size--;
        return true;
    }

    bool peek(T& value) const override {
        if (read == nullptr)
            return false;
        value = read->data;
        return true;
    }

    [[nodiscard]] int size() const override { return _size; }
};

template <typename T>
class StaticQueue : public Queue<T> {
private:
    int _capacity;
    T* _data;
    int _write = 0;
    int _read = 0;
public:
    explicit StaticQueue(const int capacity) : _capacity(capacity + 1), _data(new T[_capacity]) {}
    StaticQueue(const StaticQueue& other) : _capacity(other._capacity), _data(new T[_capacity]), _write(other._write), _read(other._read) {
        std::copy(other._data, other._data + _capacity, _data);
    }
    StaticQueue(StaticQueue&& other) noexcept : _capacity(other._capacity), _data(other._data), _write(other._write), _read(other._read) {
        other._write = other._read = 0;
        other._data = new (std::nothrow) T[other._capacity];
    }
    StaticQueue& operator=(const StaticQueue& other) {
        if (this == &other)
            return *this;
        _capacity = other._capacity;
        _data = new T[_capacity];
        std::copy(other._data, other._data + _capacity, _data);
        _write = other._write;
        _read = other._read;
        return *this;
    }
    StaticQueue& operator=(StaticQueue&& other) noexcept {
        if (this == &other)
            return *this;
        _capacity = other._capacity;
        _data = other._data;
        other._data = new (std::nothrow) T[other._capacity];
        _write = other._write;
        _read = other._read;
        other._write = other._read = 0;
        return *this;
    }
    ~StaticQueue() override {
        delete[] _data;
    }

    [[nodiscard]] Queue<T>* clone() const override {
        return new StaticQueue(*this);
    }

    bool enqueue(T value) override {
        if ((_write + 1) % _capacity != _read) {
            _data[_write] = value;
            _write = (_write + 1) % _capacity;
            return true;
        }
        return false;
    }

    bool dequeue(T& value) override {
        if (_read == _write)
            return false;
        value = _data[_read];
        _read = (_read + 1) % _capacity;
        return true;
    }

    bool peek(T& value) const override {
        if (_read != _write)
            value = _data[_read];
        return _read != _write;
    }

    [[nodiscard]] int capacity() const { return _capacity - 1; }
    [[nodiscard]] int size() const override { return (_write - _read) % _capacity; }
};

template <typename T>
class DynamicQueue : public Queue<T> {
private:
    int _capacity;
    T* _data;
    int _write = 0;
    int _read = 0;
public:
    explicit DynamicQueue(const int capacity) : _capacity(capacity + 1), _data(new T[_capacity]) {}
    DynamicQueue(const DynamicQueue& other) : _capacity(other._capacity), _data(new T[_capacity]), _write(other._write), _read(other._read) {
        std::copy(other._data, other._data + _capacity, _data);
    }
    DynamicQueue(DynamicQueue&& other) noexcept : _capacity(other._capacity), _data(other._data), _write(other._write), _read(other._read) {
        other._write = other._read = 0;
        other._capacity = 1;
        other._data = new (std::nothrow) T[other._capacity];
    }
    DynamicQueue& operator=(const DynamicQueue& other) {
        if (this == &other)
            return *this;
        _capacity = other._capacity;
        _data = new T[_capacity];
        std::copy(other._data, other._data + _capacity, _data);
        _write = other._write;
        _read = other._read;
        return *this;
    }
    DynamicQueue& operator=(DynamicQueue&& other) noexcept {
        if (this == &other)
            return *this;
        _capacity = other._capacity;
        _data = other._data;
        _write = other._write;
        _read = other._read;
        other._capacity = 1;
        other._data = new (std::nothrow) T[other._capacity];
        other._write = other._read = 0;
        return *this;
    }
    ~DynamicQueue() override {
        delete[] _data;
    }

    [[nodiscard]] Queue<T>* clone() const override {
        return new DynamicQueue(*this);
    }

    bool enqueue(T value) override {
        if ((_write + 1) % _capacity == _read) {
            _capacity *= 2;
            T* new_data = new (std::nothrow) T[_capacity];
            if (new_data == nullptr)
                return false;
            int j = 0;
            for (int i = _read; _read != _write; i = (i + 1) % _capacity, j++) {
                new_data[j] = _data[i];
            }
            delete[] _data;
            _data = new_data;
            _read = 0;
            _write = j;
        }
        _data[_write] = value;
        _write = (_write + 1) % _capacity;
        return true;
    }

    bool dequeue(T& value) override {
        if (_read == _write)
            return false;
        value = _data[_read];
        _read = (_read + 1) % _capacity;
        return true;
    }

    bool peek(T& value) const override {
        if (_read != _write)
            value = _data[_read];
        return _read != _write;
    }

    [[nodiscard]] int capacity() const { return _capacity - 1; }
    [[nodiscard]] int size() const override { return (_write - _read) % _capacity; }
};

#endif // LEETCODE_LIB_HPP
