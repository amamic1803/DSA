#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <memory>
#include <unordered_map>
#include <vector>

// template <typename T>
// class Vertex {
// private:
//     bool _visited;
//     T _data;
// public:
//     // constructors
//     explicit Vertex(T data) : _data(data), _visited(false) {}
//     Vertex(T data, bool visited) : _data(data), _visited(visited) {}
//
//     // copy constructor
//     Vertex(const Vertex& other) : _data(other._data), _visited(other._visited) {}
//
//     // move constructor
//     Vertex(Vertex&& other) noexcept : _data(std::move(other._data)), _visited(other._visited) {}
//
//     // copy assignment
//     Vertex& operator=(const Vertex& other) {
//         if (this != &other) {
//             _data = other._data;
//             _visited = other._visited;
//         }
//         return *this;
//     }
//
//     // move assignment
//     Vertex& operator=(Vertex&& other) noexcept {
//         if (this != &other) {
//             _data = std::move(other._data);
//             _visited = other._visited;
//         }
//         return *this;
//     }
//
//     // destructor
//     ~Vertex() = default;
//
//     /**
//      * Get the data of the vertex
//      * @return the data of the vertex
//      */
//     [[nodiscard]] T data() const {
//         return _data;
//     }
//
//     /**
//      * Set the data of the vertex
//      * @param data the data of the vertex
//      */
//     void set_data(T data) {
//         _data = data;
//     }
//
//     /**
//      * Check if the vertex has been visited
//      * @return true if the vertex has been visited, false otherwise
//      */
//     [[nodiscard]] bool visited() const {
//         return _visited;
//     }
//
//     /**
//      * Set the visited status of the vertex
//      * @param visited the visited status of the vertex
//      */
//     void set_visited(bool visited) {
//         _visited = visited;
//     }
// };

template <typename T>
class Graph {
private:
    struct Vertex {
        size_t _id;
        T _value;
        bool _visited;
    };
    std::unordered_map<size_t, Vertex*> _vertices;
public:
    // constructor
    Graph() = default;

    // destructor
    virtual ~Graph() {
        for (auto entry : _vertices) {
            delete entry.second;
        }
    }

    /**
     * Get the number of vertices in the graph
     * @return the number of vertices in the graph
     */
    [[nodiscard]] size_t size() const {
        return _vertices.size();
    }

    /**
     * Check if the graph is empty (no vertices)
     * @return true if the graph is empty, false otherwise
     */
    [[nodiscard]] bool empty() const {
        return size() == 0;
    }

    [[nodiscard]] virtual bool adjacent(size_t id1, size_t id2) const = 0;

    [[nodiscard]] virtual std::vector<size_t> neighbors(size_t id) const = 0;

    virtual void add_vertex(size_t id, const T& value) = 0;

    virtual void remove_vertex(size_t id) = 0;

    /**
     * Get the value of a vertex
     * @param id the id of the vertex
     * @return the value of the vertex
     */
    [[nodiscard]] const T& get_vertex_value(size_t id) const {
        return _vertices.at(id)->_value;
    }

    /**
     * Set the value of a vertex
     * @param id the id of the vertex
     * @param value the value of the vertex
     */
    void set_vertex_value(size_t id, const T& value) {
        _vertices.at(id)->_value = value;
    }

    virtual void add_edge(size_t id1, size_t id2, int weight) = 0;

    virtual void remove_edge(size_t id1, size_t id2) = 0;

    [[nodiscard]] virtual int get_edge_value(size_t id1, size_t id2) const = 0;

    virtual void set_edge_value(size_t id1, size_t id2, int weight) = 0;
};

template <typename T>
class GraphAdjacencyList : public Graph<T> {};

template <typename T>
class GraphAdjacencyMatrix : public Graph<T> {};

template <typename T>
class GraphIncidenceMatrix : public Graph<T> {};

#endif // GRAPH_HPP
