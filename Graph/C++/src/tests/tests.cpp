#include "graph.hpp"
#include "tests.hpp"
#include <cassert>
#include <string>
#include <utility>

int main(const int argc, char *argv[]) {
    if (argc != 2) {
        return -2;
    }

    const std::string arg(argv[1]);
    bool test_result;

    if (arg == "GraphAdjacencyList1")
        test_result = test_GraphAdjacencyList1();
    else if (arg == "GraphAdjacencyList2")
        test_result = test_GraphAdjacencyList2();
    else if (arg == "GraphAdjacencyList3")
        test_result = test_GraphAdjacencyList3();
    else if (arg == "GraphAdjacencyList4")
        test_result = test_GraphAdjacencyList4();
    else if (arg == "GraphAdjacencyList5")
        test_result = test_GraphAdjacencyList5();
    else if (arg == "GraphAdjacencyMatrix1")
        test_result = test_GraphAdjacencyMatrix1();
    else if (arg == "GraphAdjacencyMatrix2")
        test_result = test_GraphAdjacencyMatrix2();
    else if (arg == "GraphAdjacencyMatrix3")
        test_result = test_GraphAdjacencyMatrix3();
    else if (arg == "GraphAdjacencyMatrix4")
        test_result = test_GraphAdjacencyMatrix4();
    else if (arg == "GraphAdjacencyMatrix5")
        test_result = test_GraphAdjacencyMatrix5();
    else if (arg == "GraphIncidenceMatrix1")
        test_result = test_GraphIncidenceMatrix1();
    else if (arg == "GraphIncidenceMatrix2")
        test_result = test_GraphIncidenceMatrix2();
    else if (arg == "GraphIncidenceMatrix3")
        test_result = test_GraphIncidenceMatrix3();
    else if (arg == "GraphIncidenceMatrix4")
        test_result = test_GraphIncidenceMatrix4();
    else if (arg == "GraphIncidenceMatrix5")
        test_result = test_GraphIncidenceMatrix5();
    else
        return -3;

    return test_result ? 0 : -1;
}

bool test_GraphAdjacencyList1() {
    // Test constructors, destructors, and assignment operators
    GraphAdjacencyList<int> graph1;
    GraphAdjacencyList<int> graph2(graph1);
    const GraphAdjacencyList<int> graph3(std::move(graph1));
    graph1 = graph2;
    graph1 = std::move(graph2);
    return true;
}

bool test_GraphAdjacencyList2() {
    // Test add_vertex, remove_vertex, size, and empty
    GraphAdjacencyList<int> graph;
    graph.add_vertex(1);
    graph.add_vertex(2);
    assert(graph.size() == 2);
    assert(!graph.empty());
    graph.remove_vertex(1);
    assert(graph.size() == 1);
    graph.remove_vertex(2);
    assert(graph.empty());
    return true;
}

bool test_GraphAdjacencyList3() {
    // Test add_edge, remove_edge, and adjacent
    GraphAdjacencyList<int> graph;
    graph.add_vertex(1);
    graph.add_vertex(2);
    graph.add_edge(1, 2);
    assert(graph.adjacent(1, 2));
    graph.remove_edge(1, 2);
    assert(!graph.adjacent(1, 2));
    return true;
}

bool test_GraphAdjacencyList4() {
    // Test neighbours
    GraphAdjacencyList<int> graph;
    graph.add_vertex(1);
    graph.add_vertex(2);
    graph.add_edge(1, 2);
    const auto neighbours = graph.neighbours(1);
    assert(neighbours.size() == 1 && neighbours[0] == 2);
    return true;
}

bool test_GraphAdjacencyList5() {
    // Test vertex_visited, set_vertex_visited, and reset_vertices_visited
    GraphAdjacencyList<int> graph;
    graph.add_vertex(1);
    graph.set_vertex_visited(1, true);
    assert(graph.vertex_visited(1));
    graph.reset_vertices_visited();
    assert(!graph.vertex_visited(1));
    return true;
}

bool test_GraphAdjacencyMatrix1() {
    // Test constructors, destructors, and assignment operators
    GraphAdjacencyMatrix<int> graph1;
    GraphAdjacencyMatrix<int> graph2(graph1);
    GraphAdjacencyMatrix<int> const graph3(std::move(graph1));
    graph1 = graph2;
    graph1 = std::move(graph2);
    return true;
}

bool test_GraphAdjacencyMatrix2() {
    // Test add_vertex, remove_vertex, size, and empty
    GraphAdjacencyMatrix<int> graph;
    graph.add_vertex(1);
    graph.add_vertex(2);
    assert(graph.size() == 2);
    assert(!graph.empty());
    graph.remove_vertex(1);
    assert(graph.size() == 1);
    graph.remove_vertex(2);
    assert(graph.empty());
    return true;
}

bool test_GraphAdjacencyMatrix3() {
    // Test add_edge, remove_edge, and adjacent
    GraphAdjacencyMatrix<int> graph;
    graph.add_vertex(1);
    graph.add_vertex(2);
    graph.add_edge(1, 2);
    assert(graph.adjacent(1, 2));
    graph.remove_edge(1, 2);
    assert(!graph.adjacent(1, 2));
    return true;
}

bool test_GraphAdjacencyMatrix4() {
    // Test neighbours
    GraphAdjacencyMatrix<int> graph;
    graph.add_vertex(1);
    graph.add_vertex(2);
    graph.add_edge(1, 2);
    const auto neighbours = graph.neighbours(1);
    assert(neighbours.size() == 1 && neighbours[0] == 2);
    return true;
}

bool test_GraphAdjacencyMatrix5() {
    // Test vertex_visited, set_vertex_visited, and reset_vertices_visited
    GraphAdjacencyMatrix<int> graph;
    graph.add_vertex(1);
    graph.set_vertex_visited(1, true);
    assert(graph.vertex_visited(1));
    graph.reset_vertices_visited();
    assert(!graph.vertex_visited(1));
    return true;
}

bool test_GraphIncidenceMatrix1() {
    // Test constructors, destructors, and assignment operators
    GraphIncidenceMatrix<int> graph1;
    GraphIncidenceMatrix<int> graph2(graph1);
    const GraphIncidenceMatrix<int> graph3(std::move(graph1));
    graph1 = graph2;
    graph1 = std::move(graph2);
    return true;
}

bool test_GraphIncidenceMatrix2() {
    // Test add_vertex, remove_vertex, size, and empty
    GraphIncidenceMatrix<int> graph;
    graph.add_vertex(1);
    graph.add_vertex(2);
    assert(graph.size() == 2);
    assert(!graph.empty());
    graph.remove_vertex(1);
    assert(graph.size() == 1);
    graph.remove_vertex(2);
    assert(graph.empty());
    return true;
}

bool test_GraphIncidenceMatrix3() {
    // Test add_edge, remove_edge, and adjacent
    GraphIncidenceMatrix<int> graph;
    graph.add_vertex(1);
    graph.add_vertex(2);
    graph.add_edge(1, 2);
    assert(graph.adjacent(1, 2));
    graph.remove_edge(1, 2);
    assert(!graph.adjacent(1, 2));
    return true;
}

bool test_GraphIncidenceMatrix4() {
    // Test neighbours
    GraphIncidenceMatrix<int> graph;
    graph.add_vertex(1);
    graph.add_vertex(2);
    graph.add_edge(1, 2);
    const auto neighbours = graph.neighbours(1);
    assert(neighbours.size() == 1 && neighbours[0] == 2);
    return true;
}

bool test_GraphIncidenceMatrix5() {
    // Test vertex_visited, set_vertex_visited, and reset_vertices_visited
    GraphIncidenceMatrix<int> graph;
    graph.add_vertex(1);
    graph.set_vertex_visited(1, true);
    assert(graph.vertex_visited(1));
    graph.reset_vertices_visited();
    assert(!graph.vertex_visited(1));
    return true;
}