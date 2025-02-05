#ifndef BINARY_SEARCH_TREE_HPP
#define BINARY_SEARCH_TREE_HPP

#include <functional>
#include <memory>


template <typename T>
class BinarySearchTree {
private:
    struct Node {
        T data;
        std::unique_ptr<Node> left;
        std::unique_ptr<Node> right;

        explicit Node(const T &data) : data(data), left(nullptr), right(nullptr) {}
        Node(const T &data, std::unique_ptr<Node> left, std::unique_ptr<Node> right) : data(data), left(std::move(left)), right(std::move(right)) {}
    };

    int _size = 0;
    std::unique_ptr<Node> _root = nullptr;

    /**
     * @brief Copy a node and all its children
     * @param node The node to copy
     * @return The copied node
     */
    [[nodiscard]] std::unique_ptr<Node> copy_node(const std::unique_ptr<Node> &node) const {
        if (node) {
            std::unique_ptr<Node> new_node = std::make_unique<Node>(node->data, copy_node(node->left), copy_node(node->right));
            return new_node;
        }
        return nullptr;
    }

    /**
     * @brief Search for a value in the tree recursively
     * @param node The node to start the search from
     * @param value The value to search for
     * @return True if the value is found, false otherwise
     */
    [[nodiscard]] bool search(const std::unique_ptr<Node> &node, const T &value) const {
        if (node) {
            if (value < node->data) {
                return search(node->left, value);
            }
            if (value > node->data) {
                return search(node->right, value);
            }
            return true;
        }
        return false;
    }

    /**
     * @brief Insert a value into the tree recursively
     * @param node The node to start the insertion from
     * @param item The value to insert
     * @return True if the value is inserted, false if it is already present
     */
    bool insert(std::unique_ptr<Node> &node, const T &item) {
        if (node) {
            if (item < node->data) {
                return insert(node->left, item);
            }
            if (item > node->data) {
                return insert(node->right, item);
            }
            return false;  // item already present
        }
        node = std::make_unique<Node>(item);
        _size++;
        return true;
    }

    /**
     * @brief Remove a value from the tree recursively
     * @param node The node to start the removal from
     * @param item The value to remove
     * @return True if the value is removed, false if it is not present
     */
    bool remove(std::unique_ptr<Node> &node, const T &item) {
        if (node) {
            if (item < node->data) {
                return remove(node->left, item);
            }
            if (item > node->data) {
                return remove(node->right, item);
            }

            // current node is the node to be removed

            if (node->right == nullptr) {
                node = std::move(node->left);
            } else if (node->left == nullptr) {
                node = std::move(node->right);
            } else {
                // find rightmost node in left subtree to take place of the removed node
                std::unique_ptr<Node> *curr = &(node->left);
                while ((*curr)->right) {
                    curr = &((*curr)->right);
                }
                node->data = std::move((*curr)->data);
                *curr = std::move((*curr)->left);
            }

            _size--;
            return true;
        }
        return false;
    }

    /**
     * @brief Traverse the tree in inorder recursively
     * @param node The node to start the traversal from
     * @param func The function to call on each element
     */
    void traverseInorder(const std::unique_ptr<Node> &node, const std::function<void(const T&)> &func) const {
        if (node) {
            traverseInorder(node->left, func);
            func(node->data);
            traverseInorder(node->right, func);
        }
    }

    /**
     * @brief Traverse the tree in preorder recursively
     * @param node The node to start the traversal from
     * @param func The function to call on each element
     */
    void traversePreorder(const std::unique_ptr<Node> &node, const std::function<void(const T&)> &func) const {
        if (node) {
            func(node->data);
            traversePreorder(node->left, func);
            traversePreorder(node->right, func);
        }
    }

    /**
     * @brief Traverse the tree in postorder recursively
     * @param node The node to start the traversal from
     * @param func The function to call on each element
     */
    void traversePostorder(const std::unique_ptr<Node> &node, const std::function<void(const T&)> &func) const {
        if (node) {
            traversePostorder(node->left, func);
            traversePostorder(node->right, func);
            func(node->data);
        }
    }

    /**
     * @brief Recursive helper function to balance the tree
     * @param elements The elements to balance
     * @param start The start index
     * @param end The end index
     * @param node The node to balance
     * @return
     */
    void balance(std::vector<T> &elements, const int start, const int end, std::unique_ptr<Node> &node) {
        if (start < end) {
            const int mid = start + (end - start) / 2;
            node = std::make_unique<Node>(elements[mid]);
            balance(elements, start, mid, node->left);
            balance(elements, mid + 1, end, node->right);
        }
    }

    /**
     * @brief Recursive helper function to check if the tree is balanced
     * @param node The node to check
     * @return The height of the tree (all bits but the least significant bit) and whether the tree is balanced (the least significant bit)
     */
    int balanced_height(std::unique_ptr<Node> &node) {
        if (node) {
            const int left = balanced_height(node->left);
            const int right = balanced_height(node->right);
            const bool left_balanced = left & 1;
            const bool right_balanced = right & 1;
            const int left_height = left >> 1;
            const int right_height = right >> 1;

            const int height = std::max(left_height, right_height) + 1;
            const bool balanced = left_balanced && right_balanced && std::abs(left_height - right_height) <= 1;

            return (height << 1) | (balanced ? 1 : 0);
        }
        return 1;
    }

public:
    // constructor
    BinarySearchTree() = default;

    // copy constructor
    BinarySearchTree(const BinarySearchTree& other) : _size(other._size), _root(copy_node(other._root)) {}

    // copy assignment
    BinarySearchTree& operator=(const BinarySearchTree& other) {
        _size = other._size;
        _root = copy_node(other._root);
        return *this;
    }

    // move constructor
    BinarySearchTree(BinarySearchTree&& other) noexcept : _size(other._size), _root(std::move(other._root)) {
        other._size = 0;
        other._root = nullptr;
    }

    // move assignment
    BinarySearchTree& operator=(BinarySearchTree&& other) noexcept {
        _size = other._size;
        _root = std::move(other._root);
        other._size = 0;
        other._root = nullptr;
        return *this;
    }

    // destructor
    ~BinarySearchTree() = default;

    /**
     * @brief Get the number of elements in the tree
     * @return The number of elements in the tree
     */
    [[nodiscard]] int size() const {
        return _size;
    }

    /**
     * @brief Check if the tree is empty
     * @return
     */
    [[nodiscard]] bool empty() const {
        return _size == 0;
    }

    /**
     * @brief Search for a value in the tree
     * @param value The value to search for
     * @return True if the value is found, false otherwise
     */
    [[nodiscard]] bool search(const T &value) const {
        return search(_root, value);
    }

    /**
     * @brief Insert a value into the tree
     * @param item The value to insert
     * @return True if the value is inserted, false if it is already present
     */
    bool insert(const T &item) {
        return insert(_root, item);
    }

    /**
     * @brief Remove a value from the tree
     * @param item The value to remove
     * @return True if the value is removed, false if it is not present
     */
    bool remove(const T &item) {
        return remove(_root, item);
    }

    /**
     * @brief Traverse the tree in inorder
     * @param func The function to call on each element
     * @return
     */
    void traverseInorder(const std::function<void(const T&)> &func) const {
        traverseInorder(_root, func);
    }

    /**
     * @brief Traverse the tree in preorder
     * @param func The function to call on each element
     * @return
     */
    void traversePreorder(const std::function<void(const T&)> &func) const {
        traversePreorder(_root, func);
    }

    /**
     * @brief Traverse the tree in postorder
     * @param func The function to call on each element
     * @return
     */
    void traversePostorder(const std::function<void(const T&)> &func) const {
        traversePostorder(_root, func);
    }

    /**
     * @brief Check if the tree is balanced
     * @return True if the tree is balanced, false otherwise
     */
    [[nodiscard]] bool balanced() {
        return balanced_height(_root) & 1;
    }

    /**
     * @brief Balance the tree, expensive operation (elements are removed and tree is rebuilt).
     */
    void balance() {
        std::vector<T> elements;
        elements.reserve(_size);

        // transfer elements into array in sorted order
        traverseInorder([&elements](const T& item) {
            elements.push_back(std::move(item));
        });

        balance(elements, 0, _size, _root);
    }
};

#endif // BINARY_SEARCH_TREE_HPP
