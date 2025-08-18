#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <exception>
#include <memory>
#include <ranges>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

/**
 * Base class for exceptions thrown by the graph classes.
 */
class GraphException : public std::exception {
private:
    std::string _message;
public:
    explicit GraphException(std::string message) : _message(std::move(message)) {}

    [[nodiscard]] const char* what() const noexcept override {
        return _message.c_str();
    }
};

/**
 * Exception thrown when trying to access a vertex that does not exist.
 */
class VertexNotFoundException final : public GraphException {
public:
    explicit VertexNotFoundException(const std::string& message) : GraphException(message) {}
};

/**
 * Exception thrown when trying to access an edge that does not exist.
 */
class EdgeNotFoundException final : public GraphException {
public:
    explicit EdgeNotFoundException(const std::string& message) : GraphException(message) {}
};

/**
 * Exception thrown when trying to add a vertex that already exists.
 */
class VertexAlreadyExistsException final : public GraphException {
public:
    explicit VertexAlreadyExistsException(const std::string& message) : GraphException(message) {}
};

/**
 * Exception thrown when trying to add an edge that already exists.
 */
class EdgeAlreadyExistsException final : public GraphException {
public:
    explicit EdgeAlreadyExistsException(const std::string& message) : GraphException(message) {}
};


/**
 * The base class for directed, weighted graphs.
 */
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
     * Get the number of vertices in the graph.
     * @return The number of vertices in the graph.
     */
    [[nodiscard]] virtual size_t size() const = 0;

    /**
     * Check if the graph is empty (has no vertices).
     * @return true if the graph is empty, false otherwise.
     */
    [[nodiscard]] virtual bool empty() const {
        return size() == 0;
    }

    /**
     * Check if the vertices are adjacent in the graph.
     * @throws VertexNotFoundException If any of the vertices don't exist.
     * @param vertex1 The first vertex.
     * @param vertex2 The second vertex.
     * @return true if the vertices are adjacent, false otherwise.
     */
    [[nodiscard]] virtual bool adjacent(const T& vertex1, const T& vertex2) const = 0;

    /**
     * Get the neighbors of a vertex.
     * @throws VertexNotFoundException If the vertex doesn't exist.
     * @param vertex The vertex to get the neighbors of.
     * @return A vector with the neighbors of the vertex.
     */
    [[nodiscard]] virtual std::vector<T> neighbors(const T& vertex) const = 0;

    /**
     * Add a vertex to the graph.
     * @throws VertexAlreadyExistsException If the vertex already exists.
     * @param vertex The vertex to add.
     */
    virtual void add_vertex(const T& vertex) = 0;

    /**
     * Remove a vertex from the graph.
     * @throws VertexNotFoundException If the vertex doesn't exist.
     * @param vertex The vertex to remove.
     */
    virtual void remove_vertex(const T& vertex) = 0;

    /**
     * Add an edge (with a weight of 1) to the graph.
     *
     * The order of the vertices matters since the graph is directed.
     * @param vertex1 The first vertex.
     * @param vertex2 The second vertex.
     * @throws EdgeAlreadyExistsException If the edge already exists.
     * @throws VertexNotFoundException If any of the vertices don't exist.
     */
    virtual void add_edge(const T& vertex1, const T& vertex2) {
        if (this->get_edge_weight(vertex1, vertex2) != 0.0) {
            throw EdgeAlreadyExistsException("Edge already exists");
        }
        this->set_edge_weight(vertex1, vertex2, 1.0);
    }

    /**
     * Remove an edge (set its weight to 0) from the graph.
     *
     * The order of the vertices matters since the graph is directed.
     * @param vertex1 The first vertex.
     * @param vertex2 The second vertex.
     * @throws EdgeNotFoundException If the edge does not exist.
     * @throws VertexNotFoundException If any of the vertices don't exist.
     */
    virtual void remove_edge(const T& vertex1, const T& vertex2) {
        if (this->get_edge_weight(vertex1, vertex2) == 0.0) {
            throw EdgeNotFoundException("Edge not found");
        }
        this->set_edge_weight(vertex1, vertex2, 0.0);
    }

    /**
     * Get the weight of an edge.
     *
     * The order of the vertices matters since the graph is directed.
     * @param vertex1 The first vertex.
     * @param vertex2 The second vertex.
     * @throws VertexNotFoundException If any of the vertices don't exist.
     * @return The weight of the edge (0 if the edge doesn't exist).
     */
    [[nodiscard]] virtual double get_edge_weight(const T& vertex1, const T& vertex2) const = 0;

    /**
     * Set the weight of an edge.
     *
     * The order of the vertices matters since the graph is directed.
     * @param vertex1 The first vertex.
     * @param vertex2 The second vertex.
     * @param weight The weight of the edge (0 to remove the edge).
     * @throws VertexNotFoundException If any of the vertices don't exist.
     */
    virtual void set_edge_weight(const T& vertex1, const T& vertex2, double weight) = 0;

    /**
     * Get the visited status of a vertex.
     * @param vertex The vertex to get the visited status of.
     * @throws VertexNotFoundException If the vertex does not exist.
     * @return The visited status of the vertex.
     */
    [[nodiscard]] virtual bool get_vertex_visited(const T& vertex) const = 0;

    /**
     * Set the visited status of a vertex.
     * @param vertex The vertex to set the visited status of.
     * @param visited The new visited status of the vertex.
     * @throws VertexNotFoundException If the vertex does not exist.
     */
    virtual void set_vertex_visited(const T& vertex, bool visited) = 0;

    /**
     * Reset the visited status of all vertices (to false).
     */
    virtual void reset_vertices_visited() = 0;
};

template <typename T>
class GraphAdjacencyList : public Graph<T> {
private:
    // NOLINTBEGIN(misc-non-private-member-variables-in-classes)
    struct Vertex {
        T _value;
        std::unordered_map<size_t, double> _neighbors;
        bool _visited = false;
        Vertex() : _value(T{}) {}
        explicit Vertex(const T& value) : _value(value) {}
    };
    // NOLINTEND(misc-non-private-member-variables-in-classes)

    std::unordered_map<T, size_t> _vertices2ids;
    std::unordered_map<size_t, Vertex> _vertices;
public:
    // constructor
    GraphAdjacencyList() = default;

    // copy constructor
    GraphAdjacencyList(const GraphAdjacencyList& other) : _vertices2ids(other._vertices2ids), _vertices(other._vertices) {}

    // move constructor
    // NOLINTNEXTLINE(bugprone-exception-escape)
    GraphAdjacencyList(GraphAdjacencyList&& other) noexcept : _vertices2ids(std::move(other._vertices2ids)), _vertices(std::move(other._vertices)) {}

    // copy assignment
    GraphAdjacencyList& operator=(const GraphAdjacencyList& other) {
        if (this == &other) {
            return *this;
        }
        _vertices2ids = other._vertices2ids;
        _vertices = other._vertices;
        return *this;
    }

    // move assignment
    GraphAdjacencyList& operator=(GraphAdjacencyList&& other) noexcept {
        if (this == &other) {
            return *this;
        }
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
        size_t id1 = 0;
        size_t id2 = 0;
        try {
            id1 = _vertices2ids.at(vertex1);
        } catch (const std::out_of_range& _) {
            throw VertexNotFoundException("vertex1 not found");
        }
        try {
            id2 = _vertices2ids.at(vertex2);
        } catch (const std::out_of_range& _) {
            throw VertexNotFoundException("vertex2 not found");
        }
        return _vertices.at(id1)._neighbors.contains(id2);
    }

    [[nodiscard]] std::vector<T> neighbors(const T& vertex) const override {
        size_t id = 0;
        try {
            id = _vertices2ids.at(vertex);
        } catch (const std::out_of_range& _) {
            throw VertexNotFoundException("vertex not found");
        }
        std::vector<T> neighborsVec;
        for (const std::pair<const size_t, double>& neighbor : _vertices.at(id)._neighbors) {
            neighborsVec.push_back(_vertices.at(neighbor.first)._value);
        }
        return neighborsVec;
    }

    void add_vertex(const T& vertex) override {
        if (_vertices2ids.contains(vertex)) {
            throw VertexAlreadyExistsException("vertex already exists");
        }
        const size_t newId = size();
        _vertices2ids[vertex] = newId;
        _vertices[newId] = Vertex{vertex};
    }

    void remove_vertex(const T& vertex) override {
        size_t id = 0;
        try {
            id = _vertices2ids.at(vertex);
        } catch (const std::out_of_range& _) {
            throw VertexNotFoundException("vertex not found");
        }
        const size_t oldSize = size();
        _vertices2ids.erase(vertex);
        _vertices.erase(id);

        // update ids in _vertices2ids
        for (std::pair<const T, size_t>& vertex2id : _vertices2ids) {
            if (vertex2id.second > id) {
                --vertex2id.second;
            }
        }

        // update ids in _vertices
        for (size_t i = id + 1; i < oldSize; ++i) {
            auto node = _vertices.extract(i);
            node.key() = i - 1;
            _vertices.insert(std::move(node));
        }

        // update ids in neighbors lists
        for (std::pair<const size_t, Vertex>& vertexGraph : _vertices) {
            vertexGraph.second._neighbors.erase(id);
            std::unordered_map<size_t, double> newNeighbors;
            while (!vertexGraph.second._neighbors.empty()) {
                auto node = vertexGraph.second._neighbors.extract(vertexGraph.second._neighbors.begin());
                if (node.key() > id) {
                    node.key() -= 1; // decrement id for neighbors with id greater than removed vertex
                }
                newNeighbors.insert(std::move(node));
            }
            vertexGraph.second._neighbors = std::move(newNeighbors);
        }
    }

    [[nodiscard]] double get_edge_weight(const T& vertex1, const T& vertex2) const override {
        size_t id1 = 0;
        size_t id2 = 0;
        try {
            id1 = _vertices2ids.at(vertex1);
        } catch (const std::out_of_range& _) {
            throw VertexNotFoundException("vertex1 not found");
        }
        try {
            id2 = _vertices2ids.at(vertex2);
        } catch (const std::out_of_range& _) {
            throw VertexNotFoundException("vertex2 not found");
        }

        double weight = 0.0;
        try {
            weight = _vertices.at(id1)._neighbors.at(id2);
        } catch (const std::out_of_range& _) {}

        return weight;
    }

    void set_edge_weight(const T& vertex1, const T& vertex2, double weight) override {
        size_t id1 = 0;
        size_t id2 = 0;
        try {
            id1 = _vertices2ids.at(vertex1);
        } catch (const std::out_of_range& _) {
            throw VertexNotFoundException("vertex1 not found");
        }
        try {
            id2 = _vertices2ids.at(vertex2);
        } catch (const std::out_of_range& _) {
            throw VertexNotFoundException("vertex2 not found");
        }

        if (weight == 0.0) {
            _vertices.at(id1)._neighbors.erase(id2);
        } else {
            _vertices.at(id1)._neighbors[id2] = weight;
        }
    }

    [[nodiscard]] bool get_vertex_visited(const T& vertex) const override {
        try {
            const size_t id = _vertices2ids.at(vertex);
            return _vertices.at(id)._visited;
        } catch (const std::out_of_range& _) {
            throw VertexNotFoundException("vertex not found");
        }
    }

    void set_vertex_visited(const T& vertex, bool visited) override {
        try {
            _vertices.at(_vertices2ids.at(vertex))._visited = visited;
        } catch (const std::out_of_range& _) {
            throw VertexNotFoundException("vertex not found");
        }
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
    // NOLINTBEGIN(misc-non-private-member-variables-in-classes)
    struct Vertex {
        T _value;
        bool _visited = false;
        Vertex() : _value(T{}) {}
        explicit Vertex(const T& value) : _value(value) {}
    };
    // NOLINTEND(misc-non-private-member-variables-in-classes)

    std::unordered_map<T, size_t> _vertices2ids;
    std::unordered_map<size_t, Vertex> _vertices;
    std::unique_ptr<double[]> _adj_matrix;
public:
    // constructor
    GraphAdjacencyMatrix() = default;

    // copy constructor
    GraphAdjacencyMatrix(const GraphAdjacencyMatrix& other) : _vertices2ids(other._vertices2ids), _vertices(other._vertices), _adj_matrix(std::make_unique<double[]>(other.size() * other.size())) {
        std::copy(other._adj_matrix.get(), other._adj_matrix.get() + other.size() * other.size(), _adj_matrix.get());
    }

    // move constructor
    // NOLINTNEXTLINE(bugprone-exception-escape)
    GraphAdjacencyMatrix(GraphAdjacencyMatrix&& other) noexcept : _vertices2ids(std::move(other._vertices2ids)), _vertices(std::move(other._vertices)), _adj_matrix(std::move(other._adj_matrix)) {}

    // copy assignment
    GraphAdjacencyMatrix& operator=(const GraphAdjacencyMatrix& other) {
        if (this == &other) {
            return *this;
        }
        _vertices2ids = other._vertices2ids;
        _vertices = other._vertices;
        _adj_matrix = std::make_unique<double[]>(other.size() * other.size());
        std::copy(other._adj_matrix.get(), other._adj_matrix.get() + other.size() * other.size(), _adj_matrix.get());
        return *this;
    }

    // move assignment
    GraphAdjacencyMatrix& operator=(GraphAdjacencyMatrix&& other) noexcept {
        if (this == &other) {
            return *this;
        }
        _vertices2ids = std::move(other._vertices2ids);
        _vertices = std::move(other._vertices);
        _adj_matrix = std::move(other._adj_matrix);
        return *this;
    }

    // destructor
    ~GraphAdjacencyMatrix() override = default;

    [[nodiscard]] size_t size() const override {
        return _vertices.size();
    }

    [[nodiscard]] bool adjacent(const T& vertex1, const T& vertex2) const override {
        size_t id1 = 0;
        size_t id2 = 0;
        try {
            id1 = _vertices2ids.at(vertex1);
        } catch (const std::out_of_range& _) {
            throw VertexNotFoundException("vertex1 not found");
        }
        try {
            id2 = _vertices2ids.at(vertex2);
        } catch (const std::out_of_range& _) {
            throw VertexNotFoundException("vertex2 not found");
        }
        return _adj_matrix[id1 * size() + id2] != 0;
    }

    [[nodiscard]] std::vector<T> neighbors(const T& vertex) const override {
        size_t id = 0;
        try {
            id = _vertices2ids.at(vertex);
        } catch (const std::out_of_range& _) {
            throw VertexNotFoundException("vertex not found");
        }

        std::vector<T> neighboursVec;
        for (size_t i = id * size(); i < (id + 1) * size(); ++i) {
            if (_adj_matrix[i] != 0) {
                neighboursVec.push_back(_vertices.at(i % size())._value);
            }
        }
        return neighboursVec;
    }

    void add_vertex(const T& vertex) override {
        if (_vertices2ids.contains(vertex)) {
            throw VertexAlreadyExistsException("vertex already exists");
        }
        const size_t oldSize = size();
        _vertices2ids[vertex] = oldSize;
        _vertices[oldSize] = Vertex{vertex};

        auto newAdjMatrix = std::make_unique<double[]>(size() * size());
        for (size_t i = 0; i < oldSize; i++) {
            std::move(_adj_matrix.get() + i * oldSize, _adj_matrix.get() + (i + 1) * oldSize, newAdjMatrix.get() + i * size());
            newAdjMatrix[(i + 1) * size() - 1] = 0.0;
        }
        std::fill(newAdjMatrix.get() + (size() - 1) * size(), newAdjMatrix.get() + size() * size(), 0.0);
        _adj_matrix = std::move(newAdjMatrix);
    }

    void remove_vertex(const T& vertex) override {
        size_t id = 0;
        try {
            id = _vertices2ids.at(vertex);
        } catch (const std::out_of_range& _) {
            throw VertexNotFoundException("vertex not found");
        }
        const size_t oldSize = size();
        _vertices2ids.erase(vertex);
        _vertices.erase(id);

        // update ids in _vertices2ids
        for (std::pair<const T, size_t>& vertex2id : _vertices2ids) {
            if (vertex2id.second > id) {
                --vertex2id.second;
            }
        }

        // update ids in _vertices
        for (size_t i = id + 1; i < oldSize; ++i) {
            auto node = _vertices.extract(i);
            node.key() = i - 1;
            _vertices.insert(std::move(node));
        }

        // update adjacency matrix (remove row and column for the removed vertex)
        auto newAdjMatrix = std::make_unique<double[]>(size() * size());
        for (size_t i = 0, j = 0; i < oldSize; i++) {
            if (i != id) {
                std::move(_adj_matrix.get() + i * oldSize, _adj_matrix.get() + i * oldSize + id, &newAdjMatrix[j]);
                j += id;
                std::move(_adj_matrix.get() + i * oldSize + id + 1, _adj_matrix.get() + (i + 1) * oldSize, &newAdjMatrix[j]);
                j += oldSize - id - 1;
            }
        }
        _adj_matrix = std::move(newAdjMatrix);
    }

    [[nodiscard]] double get_edge_weight(const T& vertex1, const T& vertex2) const override {
        size_t id1 = 0;
        size_t id2 = 0;
        try {
            id1 = _vertices2ids.at(vertex1);
        } catch (const std::out_of_range& _) {
            throw VertexNotFoundException("vertex1 not found");
        }
        try {
            id2 = _vertices2ids.at(vertex2);
        } catch (const std::out_of_range& _) {
            throw VertexNotFoundException("vertex2 not found");
        }
        return _adj_matrix[id1 * size() + id2];
    }

    void set_edge_weight(const T& vertex1, const T& vertex2, const double weight) override {
        size_t id1 = 0;
        size_t id2 = 0;
        try {
            id1 = _vertices2ids.at(vertex1);
        } catch (const std::out_of_range& _) {
            throw VertexNotFoundException("vertex1 not found");
        }
        try {
            id2 = _vertices2ids.at(vertex2);
        } catch (const std::out_of_range& _) {
            throw VertexNotFoundException("vertex2 not found");
        }
        _adj_matrix[id1 * size() + id2] = weight;
    }

    [[nodiscard]] bool get_vertex_visited(const T& vertex) const override {
        try {
            const size_t id = _vertices2ids.at(vertex);
            return _vertices.at(id)._visited;
        } catch (const std::out_of_range& _) {
            throw VertexNotFoundException("vertex not found");
        }
    }

    void set_vertex_visited(const T& vertex, bool visited) override {
        try {
            _vertices.at(_vertices2ids.at(vertex))._visited = visited;
        } catch (const std::out_of_range& _) {
            throw VertexNotFoundException("vertex not found");
        }
    }

    void reset_vertices_visited() override {
        for (std::pair<const size_t, Vertex>& vertex : _vertices) {
            vertex.second._visited = false;
        }
    }
};

template <typename T>
class GraphIncidenceMatrix : public Graph<T> {
private:
    // NOLINTBEGIN(misc-non-private-member-variables-in-classes)
    struct Vertex {
        T _value;
        bool _visited = false;
        Vertex() : _value(T{}) {}
        explicit Vertex(const T& value) : _value(value) {}
    };
    // NOLINTEND(misc-non-private-member-variables-in-classes)

    std::unordered_map<T, size_t> _vertices2ids;
    std::unordered_map<size_t, Vertex> _vertices;
    size_t _edgeCount = 0;

    // (weight, outgoing edge)
    std::unique_ptr<std::pair<double, bool>[]> _inc_matrix = nullptr;
public:
    // constructor
    GraphIncidenceMatrix() = default;

    // copy constructor
    GraphIncidenceMatrix(const GraphIncidenceMatrix& other) : _vertices2ids(other._vertices2ids), _vertices(other._vertices), _edgeCount(other._edgeCount), _inc_matrix(std::make_unique<std::pair<double, bool>[]>(other.size() * other.edge_count())) {
        std::copy(other._inc_matrix.get(), other._inc_matrix.get() + other.size() * other.edge_count(), _inc_matrix.get());
    }

    // move constructor
    // NOLINTNEXTLINE(bugprone-exception-escape)
    GraphIncidenceMatrix(GraphIncidenceMatrix&& other) noexcept : _vertices2ids(std::move(other._vertices2ids)), _vertices(std::move(other._vertices)), _edgeCount(other._edgeCount), _inc_matrix(std::move(other._inc_matrix)) {}

    // copy assignment
    GraphIncidenceMatrix& operator=(const GraphIncidenceMatrix& other) {
        if (this == &other) {
            return *this;
        }
        _vertices2ids = other._vertices2ids;
        _vertices = other._vertices;
        _edgeCount = other._edgeCount;
        _inc_matrix = std::make_unique<std::pair<double, bool>[]>(other.size() * other.edge_count());
        std::copy(other._inc_matrix.get(), other._inc_matrix.get() + other.size() * other.edge_count(), _inc_matrix.get());
        return *this;
    }

    // move assignment
    GraphIncidenceMatrix& operator=(GraphIncidenceMatrix&& other) noexcept {
        if (this == &other) {
            return *this;
        }
        _vertices2ids = std::move(other._vertices2ids);
        _vertices = std::move(other._vertices);
        _edgeCount = other._edgeCount;
        _inc_matrix = std::move(other._inc_matrix);
        return *this;
    }

    // destructor
    ~GraphIncidenceMatrix() override = default;

    /**
     * Get the number of edges in the graph.
     * @return The number of edges in the graph.
     */
    [[nodiscard]] size_t edge_count() const {
        return _edgeCount;
    }

    [[nodiscard]] size_t size() const override {
        return _vertices.size();
    }

    [[nodiscard]] bool adjacent(const T& vertex1, const T& vertex2) const override {
        size_t id1 = 0;
        size_t id2 = 0;
        try {
            id1 = _vertices2ids.at(vertex1);
        } catch (const std::out_of_range& _) {
            throw VertexNotFoundException("vertex1 not found");
        }
        try {
            id2 = _vertices2ids.at(vertex2);
        } catch (const std::out_of_range& _) {
            throw VertexNotFoundException("vertex2 not found");
        }

        for (size_t j = 0; j < edge_count(); j++) {
            if (_inc_matrix[j * size() + id1].second && !_inc_matrix[j * size() + id2].second &&
                _inc_matrix[j * size() + id1].first == _inc_matrix[j * size() + id2].first &&
                _inc_matrix[j * size() + id1].first != 0.0) {
                return true;
            }
        }
        return false;
    }

    [[nodiscard]] std::vector<T> neighbors(const T& vertex) const override {
        size_t id = 0;
        try {
            id = _vertices2ids.at(vertex);
        } catch (const std::out_of_range& _) {
            throw VertexNotFoundException("vertex not found");
        }
        std::vector<T> neighboursVec;
        for (size_t j = 0; j < edge_count(); j++) {
            if (_inc_matrix[j * size() + id].second && _inc_matrix[j * size() + id].first != 0.0) {
                for (size_t i = 0; i < size(); i++) {
                    if (!_inc_matrix[j * size() + i].second &&
                        _inc_matrix[j * size() + i].first == _inc_matrix[j * size() + id].first) {
                        neighboursVec.push_back(_vertices.at(i)._value);
                        break;
                    }
                }
            }
        }
        return neighboursVec;
    }

    void add_vertex(const T& vertex) override {
        if (_vertices2ids.contains(vertex)) {
            throw VertexAlreadyExistsException("vertex already exists");
        }
        const size_t oldSize = size();
        _vertices2ids[vertex] = oldSize;
        _vertices[oldSize] = Vertex{vertex};
        auto newIncMatrix = std::make_unique<std::pair<double, bool>[]>(size() * edge_count());

        for (size_t j = 0; j < edge_count(); j++) {
            std::move(_inc_matrix.get() + j * oldSize, _inc_matrix.get() + (j + 1) * oldSize, newIncMatrix.get() + j * size());
            newIncMatrix[(j + 1) * size() - 1] = std::pair{0.0, false};
        }

        _inc_matrix = std::move(newIncMatrix);
    }

    void remove_vertex(const T& vertex) override {
        size_t id = 0;
        try {
            id = _vertices2ids.at(vertex);
        } catch (const std::out_of_range& _) {
            throw VertexNotFoundException("vertex not found");
        }
        const size_t oldSize = size();
        _vertices2ids.erase(vertex);
        _vertices.erase(id);

        // update ids in _vertices2ids
        for (std::pair<const T, size_t>& vertex2id : _vertices2ids) {
            if (vertex2id.second > id) {
                --vertex2id.second;
            }
        }

        // update ids in _vertices
        for (size_t i = id + 1; i < oldSize; ++i) {
            auto node = _vertices.extract(i);
            node.key() = i - 1;
            _vertices.insert(std::move(node));
        }

        // update edge count
        const size_t oldEdgeCount = edge_count();
        for (size_t j = 0; j < oldEdgeCount; j++) {
            if (_inc_matrix[j * oldSize + id].first != 0.0) {
                _edgeCount--;
            }
        }

        // update incidence matrix
        auto newIncMatrix = std::make_unique<std::pair<double, bool>[]>(size() * edge_count());
        for (size_t i = 0, j = 0; i < oldEdgeCount; i++) {
            if (_inc_matrix[i * oldSize + id].first == 0.0) {
                std::move(_inc_matrix.get() + i * oldSize, _inc_matrix.get() + i * oldSize + id, newIncMatrix.get() + j);
                j += id;
                std::move(_inc_matrix.get() + i * oldSize + id + 1, _inc_matrix.get() + (i + 1) * oldSize, newIncMatrix.get() + j);
                j += oldSize - id - 1;
            }
        }
        _inc_matrix = std::move(newIncMatrix);
    }

    [[nodiscard]] bool get_vertex_visited(const T& vertex) const override {
        try {
            const size_t id = _vertices2ids.at(vertex);
            return _vertices.at(id)._visited;
        } catch (const std::out_of_range& _) {
            throw VertexNotFoundException("vertex not found");
        }
    }

    void set_vertex_visited(const T& vertex, bool visited) override {
        try {
            _vertices.at(_vertices2ids.at(vertex))._visited = visited;
        } catch (const std::out_of_range& _) {
            throw VertexNotFoundException("vertex not found");
        }
    }

    void reset_vertices_visited() override {
        for (std::pair<const size_t, Vertex>& vertex : _vertices) {
            vertex.second._visited = false;
        }
    }

    [[nodiscard]] double get_edge_weight(const T& vertex1, const T& vertex2) const override {
        size_t id1 = 0;
        size_t id2 = 0;
        try {
            id1 = _vertices2ids.at(vertex1);
        } catch (const std::out_of_range& _) {
            throw VertexNotFoundException("vertex1 not found");
        }
        try {
            id2 = _vertices2ids.at(vertex2);
        } catch (const std::out_of_range& _) {
            throw VertexNotFoundException("vertex2 not found");
        }
        for (size_t j = 0; j < edge_count(); j++) {
            if (_inc_matrix[j * size() + id1].second && !_inc_matrix[j * size() + id2].second &&
                _inc_matrix[j * size() + id1].first == _inc_matrix[j * size() + id2].first &&
                _inc_matrix[j * size() + id1].first != 0.0) {
                return _inc_matrix[j * size() + id1].first;
            }
        }
        return 0;
    }

    void set_edge_weight(const T& vertex1, const T& vertex2, const double weight) override {
        size_t id1 = 0;
        size_t id2 = 0;
        try {
            id1 = _vertices2ids.at(vertex1);
        } catch (const std::out_of_range& _) {
            throw VertexNotFoundException("vertex1 not found");
        }
        try {
            id2 = _vertices2ids.at(vertex2);
        } catch (const std::out_of_range& _) {
            throw VertexNotFoundException("vertex2 not found");
        }

        // if the weight is 0, remove the edge if it is present
        if (weight == 0) {
            bool is_present = false;
            size_t edge_id = 0;
            for (size_t i = 0; i < edge_count(); i++) {
                if (_inc_matrix[i * size() + id1].second && !_inc_matrix[i * size() + id2].second &&
                    _inc_matrix[i * size() + id1].first == _inc_matrix[i * size() + id2].first &&
                    _inc_matrix[i * size() + id1].first != 0.0) {
                    is_present = true;
                    edge_id = i;
                    break;
                }
            }
            if (is_present) {
                const size_t oldEdgeCount = edge_count();
                _edgeCount--;
                auto newIncMatrix = std::make_unique<std::pair<double, bool>[]>(size() * edge_count());
                for (size_t i = 0, j = 0; i < oldEdgeCount; i++) {
                    if (i != edge_id) {
                        std::move(_inc_matrix.get() + i * size(), _inc_matrix.get() + (i + 1) * size(), newIncMatrix.get() + j);
                        j += size();
                    }
                }
                _inc_matrix = std::move(newIncMatrix);
            }
        } else {
            // if the weight is not zero, the edge must be either updated or added to the incidence matrix
            bool is_present = false;
            for (size_t i = 0; i < edge_count(); i++) {
                if (_inc_matrix[i * size() + id1].second && !_inc_matrix[i * size() + id2].second &&
                    _inc_matrix[i * size() + id1].first == _inc_matrix[i * size() + id2].first &&
                    _inc_matrix[i * size() + id1].first != 0.0) {
                        is_present = true;
                        _inc_matrix[i * size() + id1].first = _inc_matrix[i * size() + id2].first = weight;
                        break;
                    }
            }
            if (!is_present) {
                // if the edge is not present, it must be added
                const size_t oldEdgeCount = edge_count();
                _edgeCount++;
                auto newIncMatrix = std::make_unique<std::pair<double, bool>[]>(size() * edge_count());
                std::move(_inc_matrix.get(), _inc_matrix.get() + oldEdgeCount * size(), newIncMatrix.get());
                std::fill(
                    newIncMatrix.get() + oldEdgeCount * size(),
                    newIncMatrix.get() + edge_count() * size(),
                    std::pair{0.0, false}
                    );
                newIncMatrix[oldEdgeCount * size() + id1] = std::pair{weight, true};
                newIncMatrix[oldEdgeCount * size() + id2] = std::pair{weight, false};
                _inc_matrix = std::move(newIncMatrix);
            }
        }
    }
};

#endif // GRAPH_HPP
