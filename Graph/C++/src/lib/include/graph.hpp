#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <memory>
#include <ranges>
#include <stdexcept>
#include <unordered_map>
#include <unordered_set>
#include <vector>

template <typename T>
class Graph {
public:
    // constructor
    Graph() = default;

    // copy constructor
    Graph(const Graph& other) = default;

    // move constructor
    Graph(Graph&& other) noexcept = default;

    // copy assignment
    Graph& operator=(const Graph& other) = default;

    // move assignment
    Graph& operator=(Graph&& other) noexcept = default;

    // destructor
    virtual ~Graph() = default;

    /**
     * Get the number of vertices in the graph
     * @return the number of vertices in the graph
     */
    [[nodiscard]] virtual size_t size() const = 0;

    /**
     * Check if the graph is empty (no vertices)
     * @return true if the graph is empty, false otherwise
     */
    [[nodiscard]] bool empty() const {
        return size() == 0;
    }

    /**
     * Check if the vertices are adjacent in the graph
     * @param vertex1 the first vertex
     * @param vertex2 the second vertex
     * @return true if the vertices are adjacent, false otherwise
     */
    [[nodiscard]] virtual bool adjacent(const T& vertex1, const T& vertex2) const = 0;

    /**
     * Get the neighbours of a vertex
     * @param vertex the vertex to get the neighbours of
     * @return a vector containing the neighbours of the vertex
     */
    [[nodiscard]] virtual std::vector<T> neighbours(const T& vertex) const = 0;

    /**
     * Add a vertex to the graph
     * If vertex already exists, throws an exception
     * @param vertex the vertex to add
     */
    virtual void add_vertex(const T& vertex) = 0;

    /**
     * Remove a vertex from the graph
     * If the vertex does not exist, nothing happens
     * @param vertex the vertex to remove
     */
    virtual void remove_vertex(const T& vertex) = 0;

    /**
     * Add an edge to the graph (with a weight of 1, if applicable)
     * Edges are directed, so the order of the vertices matters
     * @param vertex1 the first vertex
     * @param vertex2 the second vertex
     */
     virtual void add_edge(const T& vertex1, const T& vertex2) = 0;

    /**
     * Remove an edge from the graph
     * Edges are directed, so the order of the vertices matters
     * @param vertex1 the first vertex
     * @param vertex2 the second vertex
     */
    virtual void remove_edge(const T& vertex1, const T& vertex2) = 0;

    /**
     * Get the visited status of a vertex
     * @param vertex the vertex to check
     * @return the visited status of the vertex
     */
    [[nodiscard]] virtual bool vertex_visited(const T& vertex) const = 0;

    /**
     * Set the visited status of a vertex
     * @param vertex the vertex to set
     * @param visited the new visited status of the vertex
     */
    virtual void set_vertex_visited(const T& vertex, bool visited) = 0;

    /**
     * Reset the visited status of all vertices (set to false)
     */
    virtual void reset_vertices_visited() = 0;
};

template <typename T>
class GraphAdjacencyList : public Graph<T> {
private:
    struct Vertex {
        T _value;
        std::unordered_set<size_t> _neighbours;
        bool _visited = false;

        explicit Vertex(const T& value) : _value(value) {}
    };

    std::unordered_map<T, size_t> _vertices2ids;
    std::unordered_map<size_t, Vertex> _vertices;
public:
    // constructor
    GraphAdjacencyList() = default;

    // copy constructor
    GraphAdjacencyList(const GraphAdjacencyList& other) : _vertices2ids(other._vertices2ids), _vertices(other._vertices) {}

    // move constructor
    GraphAdjacencyList(GraphAdjacencyList&& other) noexcept : _vertices2ids(std::move(other._vertices2ids)), _vertices(std::move(other._vertices)) {}

    // copy assignment
    GraphAdjacencyList& operator=(const GraphAdjacencyList& other) {
        if (this == &other)
            return *this;
        _vertices2ids = other._vertices2ids;
        _vertices = other._vertices;
        return *this;
    }

    // move assignment
    GraphAdjacencyList& operator=(GraphAdjacencyList&& other) noexcept {
        if (this == &other)
            return *this;
        _vertices2ids = std::move(other._vertices2ids);
        _vertices = std::move(other._vertices);
        return *this;
    }

    // destructor
    ~GraphAdjacencyList() override = default;

    [[nodiscard]] size_t size() const override {
        return _vertices.size();
    }

    [[nodiscard]] bool adjacent(const T& vertex1, const T& vertex2) const override {
        const size_t id1 = _vertices2ids.at(vertex1);
        const size_t id2 = _vertices2ids.at(vertex2);
        return _vertices.at(id1)._neighbours.contains(id2);
    }

    [[nodiscard]] std::vector<T> neighbours(const T& vertex) const override {
        std::vector<T> neighboursVec;
        const size_t id = _vertices2ids.at(vertex);
        for (const size_t neighbourId : _vertices.at(id)._neighbours) {
            neighboursVec.push_back(_vertices.at(neighbourId)._value);
        }
        return neighboursVec;
    }

    void add_vertex(const T& vertex) override {
        const Vertex newVertex{vertex};
        const size_t newId = _vertices.size();
        _vertices2ids[vertex] = newId;
        _vertices[newId] = newVertex;
    }

    void remove_vertex(const T& vertex) override {
        const size_t id = _vertices2ids.at(vertex);
        _vertices2ids.erase(vertex);
        for (std::pair<const T, size_t>& vertex2id : _vertices2ids) {
            if (vertex2id.second > id) {
                vertex2id.second--;
            }
        }
        _vertices.erase(id);
        for (std::pair<const size_t, Vertex>& vertexGraph : _vertices) {
            std::unordered_set<size_t> newNeighbours;
            newNeighbours.reserve(vertexGraph.second._neighbours.size());
            for (const size_t& neighbourId : vertexGraph.second._neighbours) {
                if (neighbourId < id) {
                    newNeighbours.insert(neighbourId);
                } else if (neighbourId > id) {
                    newNeighbours.insert(neighbourId - 1);
                }
            }
            vertexGraph.second._neighbours = std::move(newNeighbours);
        }
    }

    void add_edge(const T& vertex1, const T& vertex2) override {
        const size_t id1 = _vertices2ids.at(vertex1);
        const size_t id2 = _vertices2ids.at(vertex2);
        _vertices.at(id1)._neighbours.insert(id2);
    }

    void remove_edge(const T& vertex1, const T& vertex2) override {
        const size_t id1 = _vertices2ids.at(vertex1);
        const size_t id2 = _vertices2ids.at(vertex2);
        _vertices.at(id1)._neighbours.erase(id2);
    }

    [[nodiscard]] bool vertex_visited(const T& vertex) const override {
        return _vertices.at(_vertices2ids.at(vertex))._visited;
    }

    void set_vertex_visited(const T& vertex, bool visited) override {
        const size_t id = _vertices2ids.at(vertex);
        Vertex& vertexGraph = _vertices.at(id);
        vertexGraph._visited = visited;
    }

    void reset_vertices_visited() override {
        for (std::pair<const size_t, Vertex>& vertex : _vertices) {
            vertex.second._visited = false;
        }
    }
};

template <typename T>
class GraphAdjacencyMatrix : public Graph<T> {
private:
    struct Vertex {
        T _value;
        bool _visited = false;
        explicit Vertex(const T& value) : _value(value) {}
    };

    std::unordered_map<T, size_t> _vertices2ids;
    std::unordered_map<size_t, Vertex> _vertices;
    double* _adj_matrix = nullptr;
public:
    // constructor
    GraphAdjacencyMatrix() = default;

    // copy constructor
    GraphAdjacencyMatrix(const GraphAdjacencyMatrix& other) : _vertices2ids(other._vertices2ids), _vertices(other._vertices), _adj_matrix(static_cast<double*>(malloc(other.size() * other.size() * sizeof(double)))) {
        if (_adj_matrix == nullptr) {
            throw std::bad_alloc();
        }
        std::copy(other._adj_matrix, other._adj_matrix + other.size() * other.size(), _adj_matrix);
    }

    // move constructor
    GraphAdjacencyMatrix(GraphAdjacencyMatrix&& other) noexcept : _vertices2ids(std::move(other._vertices2ids)), _vertices(std::move(other._vertices)), _adj_matrix(other._adj_matrix) {
        other._adj_matrix = nullptr;
    }

    // copy assignment
    GraphAdjacencyMatrix& operator=(const GraphAdjacencyMatrix& other) {
        if (this == &other)
            return *this;
        _vertices2ids = other._vertices2ids;
        _vertices = other._vertices;
        _adj_matrix = static_cast<double*>(malloc(other.size() * other.size() * sizeof(double)));
        if (_adj_matrix == nullptr) {
            throw std::bad_alloc();
        }
        std::copy(other._adj_matrix, other._adj_matrix + other.size() * other.size(), _adj_matrix);
        return *this;
    }

    // move assignment
    GraphAdjacencyMatrix& operator=(GraphAdjacencyMatrix&& other) noexcept {
        if (this == &other)
            return *this;
        _vertices2ids = std::move(other._vertices2ids);
        _vertices = std::move(other._vertices);
        _adj_matrix = other._adj_matrix;
        other._adj_matrix = nullptr;
        return *this;
    }

    // destructor
    ~GraphAdjacencyMatrix() override {
        free(_adj_matrix);
    }

    [[nodiscard]] size_t size() const override {
        return _vertices.size();
    }

    [[nodiscard]] bool adjacent(const T& vertex1, const T& vertex2) const override {
        const size_t id1 = _vertices2ids.at(vertex1);
        const size_t id2 = _vertices2ids.at(vertex2);
        return _adj_matrix[id1 * size() + id2] != 0;
    }

    [[nodiscard]] std::vector<T> neighbours(const T& vertex) const override {
        std::vector<T> neighboursVec;
        const size_t id = _vertices2ids.at(vertex);
        for (size_t i = id * size(); i < (id + 1) * size(); i++) {
            if (_adj_matrix[i] != 0) {
                neighboursVec.push_back(_vertices.at(i % size())._value);
            }
        }
        return neighboursVec;
    }

    void add_vertex(const T& vertex) override {
        const size_t oldSize = size();
        _vertices2ids[vertex] = oldSize;
        const Vertex newVertex{vertex};
        _vertices[oldSize] = newVertex;
        _adj_matrix = static_cast<double*>(realloc(_adj_matrix, size() * size() * sizeof(double)));
        if (_adj_matrix == nullptr) {
            throw std::bad_alloc();
        }
        for (size_t i = size() - 2; i != static_cast<size_t>(-1); i++) {
            for (size_t j = size() - 2; j != static_cast<size_t>(-1); j++) {
                _adj_matrix[i * size() + j] = _adj_matrix[i * oldSize + j];
            }
        }
    }

    void remove_vertex(const T& vertex) override {
        const size_t oldSize = size();
        const size_t id = _vertices2ids.at(vertex);
        _vertices2ids.erase(vertex);
        _vertices.erase(id);
        double* _adj_matrix_ptr = _adj_matrix;
        for (size_t i = 0; i < oldSize; i++) {
            if (i == id) {
                continue;
            }
            for (size_t j = 0; j < oldSize; j++) {
                if (j == id) {
                    continue;
                }
                *(_adj_matrix_ptr++) = _adj_matrix[i * oldSize + j];
            }
        }
        _adj_matrix = static_cast<double*>(realloc(_adj_matrix, size() * size() * sizeof(double)));
        if (_adj_matrix == nullptr) {
            throw std::bad_alloc();
        }
    }

    void add_edge(const T& vertex1, const T& vertex2) override {
        set_edge_value(vertex1, vertex2, 1);
    }

    void remove_edge(const T& vertex1, const T& vertex2) override {
        set_edge_value(vertex1, vertex2, 0);
    }

    [[nodiscard]] bool vertex_visited(const T& vertex) const override {
        const size_t id = _vertices2ids.at(vertex);
        return _vertices.at(id)._visited;
    }

    void set_vertex_visited(const T& vertex, bool visited) override {
        const size_t id = _vertices2ids.at(vertex);
        _vertices.at(id)._visited = visited;
    }

    void reset_vertices_visited() override {
        for (std::pair<const size_t, Vertex>& vertex : _vertices) {
            vertex.second._visited = false;
        }
    }

    /**
     * Get the value of an edge
     * @param vertex1 the first vertex
     * @param vertex2 the second vertex
     * @return the weight of the edge (0 means no edge, 1 if not weighted)
     */
    [[nodiscard]] double get_edge_value(const T& vertex1, const T& vertex2) const {
        const size_t id1 = _vertices2ids.at(vertex1);
        const size_t id2 = _vertices2ids.at(vertex2);
        return _adj_matrix[id1 * size() + id2];
    }

    /**
     * Set the value of an edge
     * @param vertex1 the first vertex
     * @param vertex2 the second vertex
     * @param weight the weight of the edge (0 means no edge)
     */
    void set_edge_value(const T& vertex1, const T& vertex2, const double weight) {
        const size_t id1 = _vertices2ids.at(vertex1);
        const size_t id2 = _vertices2ids.at(vertex2);
        _adj_matrix[id1 * size() + id2] = weight;
    }
};

template <typename T>
class GraphIncidenceMatrix : public Graph<T> {
private:
    struct Vertex {
        T _value;
        bool _visited = false;
        explicit Vertex(const T& value) : _value(value) {}
    };

    std::unordered_map<T, size_t> _vertices2ids;
    std::unordered_map<size_t, Vertex> _vertices;
    size_t _edgeCount = 0;
    double* _inc_matrix = nullptr;
public:
    // constructor
    GraphIncidenceMatrix() = default;

    // copy constructor
    GraphIncidenceMatrix(const GraphIncidenceMatrix& other) : _vertices2ids(other._vertices2ids), _vertices(other._vertices), _edgeCount(other._edgeCount), _inc_matrix(static_cast<double*>(malloc(other.size() * other.edge_count() * sizeof(double)))) {
        if (_inc_matrix == nullptr) {
            throw std::bad_alloc();
        }
        std::copy(other._inc_matrix, other._inc_matrix + other.size() * other.edge_count(), _inc_matrix);
    }

    // move constructor
    GraphIncidenceMatrix(GraphIncidenceMatrix&& other) noexcept : _vertices2ids(std::move(other._vertices2ids)), _vertices(std::move(other._vertices)), _edgeCount(other._edgeCount), _inc_matrix(other._inc_matrix) {
        other._inc_matrix = nullptr;
        other._edgeCount = 0;
    }

    // copy assignment
    GraphIncidenceMatrix& operator=(const GraphIncidenceMatrix& other) {
        if (this == &other)
            return *this;
        _vertices2ids = other._vertices2ids;
        _vertices = other._vertices;
        _edgeCount = other._edgeCount;
        _inc_matrix = static_cast<double*>(malloc(other.size() * other.edge_count() * sizeof(double)));
        if (_inc_matrix == nullptr) {
            throw std::bad_alloc();
        }
        std::copy(other._inc_matrix, other._inc_matrix + other.size() * other.edge_count(), _inc_matrix);
        return *this;
    }

    // move assignment
    GraphIncidenceMatrix& operator=(GraphIncidenceMatrix&& other) noexcept {
        if (this == &other)
            return *this;
        _vertices2ids = std::move(other._vertices2ids);
        _vertices = std::move(other._vertices);
        _edgeCount = other._edgeCount;
        _inc_matrix = other._inc_matrix;
        other._inc_matrix = nullptr;
        other._edgeCount = 0;
        return *this;
    }

    // destructor
    ~GraphIncidenceMatrix() override {
        free(_inc_matrix);
    }

    /**
     * Get the number of edges in the graph
     * @return the number of edges in the graph
     */
    [[nodiscard]] size_t edge_count() const {
        return _edgeCount;
    }

    [[nodiscard]] size_t size() const override {
        return _vertices.size();
    }

    [[nodiscard]] bool adjacent(const T& vertex1, const T& vertex2) const override {
        const size_t id1 = _vertices2ids.at(vertex1);
        const size_t id2 = _vertices2ids.at(vertex2);
        for (int j = 0; j < edge_count(); j++) {
            if (_inc_matrix[id1 * edge_count() + j] > 0 && _inc_matrix[id2 * edge_count() + j] < 0) {
                return true;
            }
        }
        return false;
    }

    [[nodiscard]] std::vector<T> neighbours(const T& vertex) const override {
        std::vector<T> neighboursVec;
        const size_t id = _vertices2ids.at(vertex);
        for (int j = 0; j < edge_count(); j++) {
            if (_inc_matrix[id * edge_count() + j] > 0) {
                for (int i = 0; i < size(); i++) {
                    if (_inc_matrix[i * edge_count() + j] < 0) {
                        neighboursVec.push_back(_vertices.at(i)._value);
                        break;
                    }
                }
            }
        }
        return neighboursVec;
    }

    void add_vertex(const T& vertex) override {
        const size_t id = _vertices.size();
        _vertices2ids[vertex] = id;
        Vertex newVertex{vertex};
        _vertices[id] = std::move(newVertex);
        _inc_matrix = static_cast<double*>(realloc(_inc_matrix, size() * edge_count() * sizeof(double)));
        if (_inc_matrix == nullptr) {
            throw std::bad_alloc();
        }
    }

    void remove_vertex(const T& vertex) override {
        const size_t id = _vertices2ids.at(vertex);
        _vertices2ids.erase(vertex);
        _vertices.erase(id);

        int i = 0;
        for (int j = 0; j < edge_count(); j++) {
            if (_inc_matrix[id * edge_count() + j] == 0) {
                for (int k = 0; k < size(); k++) {
                    _inc_matrix[k * edge_count() + i] = _inc_matrix[k * edge_count() + j];
                }
                i++;
            }
        }
        const int removed_edges = edge_count() - i;
        i = 0;
        for (int j = 0; j < size(); j++) {
            if (j != id) {
                std::copy(&_inc_matrix[j * edge_count()], &_inc_matrix[(j + 1) * edge_count()], &_inc_matrix[i]);
                i += edge_count() - removed_edges;
            }
        }
        _edgeCount -= removed_edges;

        _inc_matrix = static_cast<double*>(realloc(_inc_matrix, size() * edge_count() * sizeof(double)));
        if (_inc_matrix == nullptr) {
            throw std::bad_alloc();
        }
    }

    void add_edge(const T& vertex1, const T& vertex2) override {
        set_edge_value(vertex1, vertex2, 1);
    }

    void remove_edge(const T& vertex1, const T& vertex2) override {
        set_edge_value(vertex1, vertex2, 0);
    }

    [[nodiscard]] bool vertex_visited(const T& vertex) const override {
        const size_t id = _vertices2ids.at(vertex);
        return _vertices.at(id)._visited;
    }

    void set_vertex_visited(const T& vertex, bool visited) override {
        const size_t id = _vertices2ids.at(vertex);
        _vertices.at(id)._visited = visited;
    }

    void reset_vertices_visited() override {
        for (const std::pair<const size_t, Vertex>& pair : _vertices) {
            _vertices[pair.first]._visited = false;
        }
    }

    /**
     * Get the value of an edge
     * @param vertex1 the first vertex
     * @param vertex2 the second vertex
     * @return the weight of the edge (0 means no edge, 1 if not weighted)
     */
    [[nodiscard]] double get_edge_value(const T& vertex1, const T& vertex2) const {
        const size_t id1 = _vertices2ids.at(vertex1);
        const size_t id2 = _vertices2ids.at(vertex2);
        for (int j = 0; j < edge_count(); j++) {
            if (_inc_matrix[id1 * edge_count() + j] > 0 && _inc_matrix[id2 * edge_count() + j] < 0) {
                return _inc_matrix[id1 * edge_count() + j];
            }
        }
        return 0;
    }

    /**
     * Set the value of an edge
     * @param vertex1 the first vertex
     * @param vertex2 the second vertex
     * @param weight the weight of the edge (0 means no edge)
     */
    void set_edge_value(const T& vertex1, const T& vertex2, const double weight) {
        const size_t id1 = _vertices2ids.at(vertex1);
        const size_t id2 = _vertices2ids.at(vertex2);

        // update edge if it is already in the incidence matrix
        for (int j = 0; j < edge_count(); j++) {
            if (_inc_matrix[id1 * edge_count() + j] > 0 && _inc_matrix[id2 * edge_count() + j] < 0) {
                _inc_matrix[id1 * edge_count() + j] = weight;
                _inc_matrix[id2 * edge_count() + j] = -weight;
                return;
            }
        }

        // if edge is not in incidence matrix
        _edgeCount++;
        _inc_matrix = static_cast<double*>(realloc(_inc_matrix, size() * edge_count() * sizeof(double)));
        if (_inc_matrix == nullptr) {
            throw std::bad_alloc();
        }
        for (size_t i = size() - 1; i != static_cast<size_t>(-1); i++) {
            for (size_t j = edge_count() - 2; j != static_cast<size_t>(-1); j++) {
                _inc_matrix[i * edge_count() + j] = _inc_matrix[i * (edge_count() - 1) + j];
            }
        }
    }
};

#endif // GRAPH_HPP
