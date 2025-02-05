#ifndef BINARY_HEAP_HPP
#define BINARY_HEAP_HPP

#include <algorithm>
#include <cmath>
#include <stdexcept>


// implementation of max binary heap
template <typename T>
class BinaryHeap {
private:
    T *_heap = nullptr;
    int _size = 0;
    int _capacity = 0;

    /**
     * @brief Increase the capacity of the heap.
     *
     * Always increases the capacity by adding one level to the tree which means that the new capacity is (2 * old_capacity + 1).
     */
    void increase_capacity() {
        const int k = std::log2(_capacity + 1) + 1;  // new number of levels
        _capacity = std::pow(2, k) - 1;  // new capacity
        _heap = static_cast<T*>(realloc(_heap, _capacity * sizeof(T)));
        if (_heap == nullptr) {
            _capacity = 0;
            _size = 0;
            throw std::bad_alloc();
        }
    }

    /**
     * @brief Reserve capacity for the heap.
     *
     * If the new capacity is less than or equal to the current capacity, nothing is done.
     * Allocated capacity might be greater than the requested capacity because capacity for the full binary tree is allocated.
     *
     * @param capacity The new capacity.
     */
    void reserve_capacity(const int capacity) {
        if (capacity <= _capacity) {
            return;
        }
        const int k = static_cast<int>(std::ceil(std::log2(static_cast<double>(capacity) + 1)));  // number of levels
        _capacity = static_cast<int>(std::pow(2, k)) - 1;  // new capacity
        _heap = static_cast<T*>(realloc(_heap, _capacity * sizeof(T)));
        if (_heap == nullptr) {
            _capacity = 0;
            _size = 0;
            throw std::bad_alloc();
        }
    }

    /**
     * @brief Swap two elements in the heap.
     * @param i The index of the first element.
     * @param j The index of the second element.
     */
    void swap(int i, int j) {
        T temp = std::move(_heap[i]);
        _heap[i] = std::move(_heap[j]);
        _heap[j] = std::move(temp);
    }

    /**
     * @brief Heapify the heap starting from the given index (node).
     * @param i The index (node) to start heapifying from.
     */
    void heapify(const int i) {
        const int left = (i << 1) + 1;
        const int right = (i << 1) + 2;

        int largest = i;
        if (left < _size && _heap[left] > _heap[largest]) {
            largest = left;
        }
        if (right < _size && _heap[right] > _heap[largest]) {
            largest = right;
        }

        if (largest != i) {
            swap(i, largest);
            heapify(largest);
        }
    }

    /**
     * @brief Search for an element in the heap recursively.
     * @param item The element to search for.
     * @param i The index of the current node.
     */
    [[nodiscard]] bool search_rec(const T& item, const int i) const {
        if (i >= _size || _heap[i] < item) {
            return false;
        }
        if (item == _heap[i]) {
            return true;
        }
        const int left = (i << 1) + 1;
        const int right = (i << 1) + 2;
        return search_rec(item, left) || search_rec(item, right);
    }
public:
    // default constructor
    BinaryHeap() = default;

    /**
     * @brief Construct a new Binary Heap object from an array of elements.
     * @param elements The array of elements.
     * @param n The number of elements in the array.
     */
    BinaryHeap(const T* elements, const int n) : _size(n) {
        reserve_capacity(_size);
        std::copy(elements, elements + _size, _heap);
        for (int i = (n >> 1) - 1; i >= 0; i--) {
            heapify(i);
        }
    }

    // copy constructor
    BinaryHeap(const BinaryHeap &other) : _size(other._size), _capacity(other._capacity) {
        _heap = static_cast<T*>(realloc(_heap, _capacity * sizeof(T)));
        if (_heap == nullptr) {
            _capacity = 0;
            _size = 0;
            throw std::bad_alloc();
        }
        std::copy(other._heap, other._heap + other._size, _heap);
    }

    // move constructor
    BinaryHeap(BinaryHeap &&other) noexcept : _size(other._size), _capacity(other._capacity) {
        free(_heap);
        _heap = other._heap;
        other._heap = nullptr;
        other._size = 0;
        other._capacity = 0;
    }

    // copy assignment
    BinaryHeap &operator=(const BinaryHeap &other) {
        if (this != &other) {
            _size = other._size;
            _capacity = other._capacity;
            _heap = static_cast<T*>(realloc(_heap, _capacity * sizeof(T)));
            if (_heap == nullptr) {
                _capacity = 0;
                _size = 0;
                throw std::bad_alloc();
            }
            std::copy(other._heap, other._heap + other._size, _heap);
        }
        return *this;
    }

    // move assignment
    BinaryHeap &operator=(BinaryHeap &&other) noexcept {
        if (this != &other) {
            free(_heap);
            _heap = other._heap;
            _size = other._size;
            _capacity = other._capacity;
            other._heap = nullptr;
            other._size = 0;
            other._capacity = 0;
        }
        return *this;
    }

    // destructor
    ~BinaryHeap() {
        free(_heap);
    }

    /**
     * @brief Get the number of elements in the heap.
     * @return The number of elements in the heap.
     */
    [[nodiscard]] int size() const {
        return _size;
    }

    /**
     * @brief Check if the heap is empty.
     * @return true if the heap is empty, false otherwise.
     */
    [[nodiscard]] bool empty() const {
        return _size == 0;
    }

    /**
     * @brief Insert a new element into the heap.
     * @param item The new element.
     */
    void insert(const T& item) {
        if (_size == _capacity) {
            increase_capacity();
        }
        _heap[_size] = item;
        int tmp = _size++;
        while (tmp != 0) {
            if (_heap[tmp] > _heap[(tmp - 1) >> 1]) {
                swap(tmp, (tmp - 1) >> 1);
                tmp = (tmp - 1) >> 1;
            } else {
                break;
            }
        }
    }

    /**
     * @brief Check if the item is in the heap.
     * @param item
     * @return true if the item is in the heap, false otherwise.
     */
    [[nodiscard]] bool search(const T& item) const {
        return search_rec(item, 0);
    }

    /**
     * @brief Get the maximum element from the heap.
     * @return
     */
    [[nodiscard]] const T& peek() const {
        if (_size == 0) {
            throw std::out_of_range("Heap is empty");
        }
        return _heap[0];
    }

    /**
     * @brief Remove the maximum element from the heap.
     * @return The maximum element.
     */
    T pop() {
        if (_size == 0) {
            throw std::out_of_range("Heap is empty");
        }
        T element = std::move(_heap[0]);
        _heap[0] = std::move(_heap[--_size]);
        heapify(0);
        return element;
    }
};

#endif // BINARY_HEAP_HPP
