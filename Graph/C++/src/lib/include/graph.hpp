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
private:
    struct Vertex {
        size_t _id;
        T _value;
    };

    std::unordered_map<size_t, Vertex> _vertices;
public:
    // constructor
    Graph() = default;

    // copy constructor
    Graph(const Graph& other) : _vertices(other._vertices) {}

    // move constructor
    Graph(Graph&& other) noexcept : _vertices(std::move(other._vertices)) {}

    // copy assignment
    Graph& operator=(const Graph& other) {
        if (this == &other)
            return *this;
        _vertices = other._vertices;
        return *this;
    }

    // move assignment
    Graph& operator=(Graph&& other) noexcept {
        if (this == &other)
            return *this;
        _vertices = std::move(other._vertices);
        return *this;
    }

    // destructor
    virtual ~Graph() = default;

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

    /**
     * Check if the vertices are adjacent in the graph
     * @param id1 the id of the first vertex
     * @param id2 the id of the second vertex
     * @return true if the vertices are adjacent, false otherwise
     */
    [[nodiscard]] virtual bool adjacent(size_t id1, size_t id2) const = 0;

    /**
     * Get the neighbors of a vertex
     * @param id the id of the vertex
     * @return a vector containing the ids of the neighbors of the vertex
     */
    [[nodiscard]] virtual std::vector<size_t> neighbors(size_t id) const = 0;

    /**
     * Add a vertex to the graph
     * If vertex already exists, throws an exception
     * @param id the id of the vertex
     * @param value the value of the vertex
     */
    virtual void add_vertex(size_t id, const T& value) {
        if (_vertices.contains(id)) {
            throw std::invalid_argument("Vertex already exists");
        }
        Vertex new_vertex{id, value};
        _vertices[id] = new_vertex;
    }

    /**
     * Remove a vertex from the graph
     * If the vertex does not exist, nothing happens
     * @param id the id of the vertex to remove
     */
    virtual void remove_vertex(size_t id) {
        _vertices.erase(id);
    }

    /**
     * Get the value of a vertex
     * @param id the id of the vertex
     * @return the value of the vertex
     */
    [[nodiscard]] T& get_vertex_value(size_t id) const {
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

    /**
     * Add an edge to the graph
     * @param id1 the id of the first vertex
     * @param id2 the id of the second vertex
     * @param weight the weight of the edge (0 means no edge, 1 if not weighted)
     */
    void add_edge(const size_t id1, const size_t id2, const double weight) {
        set_edge_value(id1, id2, weight);
    }

    /**
     * Remove an edge from the graph
     * @param id1 the id of the first vertex
     * @param id2 the id of the second vertex
     */
    void remove_edge(const size_t id1, const size_t id2) {
        set_edge_value(id1, id2, 0);
    }

    /**
     * Get the value of an edge
     * @param id1 the id of the first vertex
     * @param id2 the id of the second vertex
     * @return the weight of the edge (0 means no edge, 1 if not weighted)
     */
    [[nodiscard]] virtual double get_edge_value(size_t id1, size_t id2) const = 0;

    /**
     * Set the value of an edge
     * @param id1 the id of the first vertex
     * @param id2 the id of the second vertex
     * @param weight the weight of the edge (0 means no edge)
     */
    virtual void set_edge_value(size_t id1, size_t id2, double weight) = 0;
};

template <typename T>
class GraphAdjacencyList : public Graph<T> {
private:
    struct PairHash {
        template <typename T1, typename T2>
        std::size_t operator()(const std::pair<T1, T2>& p) const {
            return std::hash<T1>()(p.first) ^ std::hash<T2>()(p.second);
        }
    };
    struct PairEqual {
        template <typename T1, typename T2>
        bool operator()(const std::pair<T1, T2>& lhs, const std::pair<T1, T2>& rhs) const {
            return lhs.first == rhs.first && lhs.second == rhs.second;
        }
    };

    std::unordered_set<std::pair<size_t, size_t>, PairHash, PairEqual> _edges;
public:
    // constructor
    GraphAdjacencyList() = default;

    // copy constructor
    GraphAdjacencyList(const GraphAdjacencyList& other) : Graph<T>(other), _edges(other._edges) {}

    // move constructor
    GraphAdjacencyList(GraphAdjacencyList&& other) noexcept : Graph<T>(std::move(other)), _edges(std::move(other._edges)) {}

    // copy assignment
    GraphAdjacencyList& operator=(const GraphAdjacencyList& other) {
        if (this == &other)
            return *this;
        Graph<T>::operator =(other);
        _edges = other._edges;
        return *this;
    }

    // move assignment
    GraphAdjacencyList& operator=(GraphAdjacencyList&& other) noexcept {
        if (this == &other)
            return *this;
        Graph<T>::operator =(std::move(other));
        _edges = std::move(other._edges);
        return *this;
    }

    // destructor
    ~GraphAdjacencyList() override = default;

    [[nodiscard]] bool adjacent(const size_t id1, const size_t id2) const override {
        return _edges.contains({id1, id2});
    }

    [[nodiscard]] std::vector<size_t> neighbors(const size_t id) const override {
        std::vector<size_t> neighbors;
        for (const auto& [first, second] : _edges) {
            if (first == id) {
                neighbors.push_back(second);
            }
        }
        return neighbors;
    }

    void add_vertex(size_t id, const T& value) override {
        Graph<T>::add_vertex(id, value);
    }

    void remove_vertex(size_t id) override {
        Graph<T>::remove_vertex(id);
        std::erase_if(_edges, [id](const std::pair<size_t, size_t>& edge) {
            return edge.first == id || edge.second == id;
        });
    }

    [[nodiscard]] double get_edge_value(size_t id1, size_t id2) const override {
        const std::pair edge{id1, id2};
        const bool edge_exists = std::ranges::find(_edges, edge) != _edges.end();
        return edge_exists ? 1 : 0;
    }

    void set_edge_value(const size_t id1, const size_t id2, const double weight) override {
        if (weight == 0) {
            _edges.erase({id1, id2});
        } else {
            _edges.insert({id1, id2});
        }
    }
};

template <typename T>
class GraphAdjacencyMatrix : public Graph<T> {
private:
    double* _adj_matrix;
public:
    GraphAdjacencyMatrix() : _adj_matrix(nullptr) {}

    [[nodiscard]] bool adjacent(size_t id1, size_t id2) const override {
        return _adj_matrix[id1 * this->size() + id2] != 0;
    }

    [[nodiscard]] std::vector<size_t> neighbors(size_t id) const override {
        std::vector<size_t> neighbors;
        for (int ind = id * this->size(); ind < (id + 1) * this->size(); ind++) {
            if (_adj_matrix[ind] != 0) {
                neighbors.push_back(ind % this->size());
            }
        }
        return neighbors;
    }

    void add_vertex(size_t id, const T& value) override;
    void remove_vertex(size_t id) override;
    [[nodiscard]] double get_edge_value(size_t id1, size_t id2) const override;
    void set_edge_value(size_t id1, size_t id2, double weight) override;
    ~GraphAdjacencyMatrix() override;
};

template <typename T>
class GraphIncidenceMatrix : public Graph<T> {};

#endif // GRAPH_HPP
