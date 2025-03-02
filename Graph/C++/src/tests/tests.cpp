#include "graph.hpp"
#include "tests.hpp"
#include <algorithm>
#include <string>
#include <utility>
#include <vector>

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
    graph1.add_vertex(1);
    graph1.add_vertex(2);
    graph1.add_edge(1, 2);
    graph1.add_edge(2, 1);
    GraphAdjacencyList<int> graph2{graph1};
    if (!graph2.adjacent(1, 2) || !graph2.adjacent(2, 1)) {
        return false;
    }
    const GraphAdjacencyList<int> graph3{std::move(graph1)};
    if (!graph3.adjacent(1, 2) || !graph3.adjacent(2, 1)) {
        return false;
    }
    graph1 = graph2;
    if (!graph1.adjacent(1, 2) || !graph1.adjacent(2, 1)) {
        return false;
    }
    graph1 = std::move(graph2);
    return graph1.adjacent(1, 2) && graph1.adjacent(2, 1);
}

bool test_GraphAdjacencyList2() {
    // Test add_vertex, remove_vertex, size, and empty
    GraphAdjacencyList<int> graph;
    graph.add_vertex(1);
    graph.add_vertex(2);
    if (graph.size() != 2 || graph.empty()) {
        return false;
    }
    graph.remove_vertex(1);
    if (graph.size() != 1 || graph.empty()) {
        return false;
    }
    graph.add_vertex(3);
    if (graph.size() != 2 || graph.empty()) {
        return false;
    }
    graph.remove_vertex(2);
    if (graph.size() != 1 || graph.empty()) {
        return false;
    }
    graph.remove_vertex(3);
    return graph.empty();
}

bool test_GraphAdjacencyList3() {
    // Test add_edge, remove_edge, and adjacent
    GraphAdjacencyList<int> graph;
    graph.add_vertex(1);
    graph.add_vertex(2);
    graph.add_edge(1, 2);
    if (!graph.adjacent(1, 2) || graph.adjacent(2, 1)) { return false; }
    graph.add_edge(2, 1);
    if (!graph.adjacent(1, 2) || !graph.adjacent(2, 1)) { return false; }
    graph.add_vertex(3);
    if (graph.adjacent(1, 3) || graph.adjacent(3, 1) || graph.adjacent(2, 3) || graph.adjacent(3, 2)) {
        return false;
    }
    graph.remove_edge(1, 2);
    if (graph.adjacent(1, 2) || !graph.adjacent(2, 1)) { return false; }
    graph.remove_vertex(2);
    return !graph.adjacent(1, 3) && !graph.adjacent(3, 1);
}

bool test_GraphAdjacencyList4() {
    // Test neighbours
    GraphAdjacencyList<int> graph;
    graph.add_vertex(1);
    graph.add_vertex(2);
    graph.add_vertex(4);
    graph.add_edge(1, 2);
    graph.add_edge(2, 4);
    graph.add_edge(1, 4);
    auto neighbours1 = graph.neighbours(1);
    std::ranges::sort(neighbours1);
    const std::vector<int> expectedNeighbours1{2, 4};
    if (neighbours1 != expectedNeighbours1) {
        return false;
    }
    const auto neighbours2 = graph.neighbours(2);
    const std::vector<int> expectedNeighbours2{4};
    return neighbours2 == expectedNeighbours2;
}

bool test_GraphAdjacencyList5() {
    // Test vertex_visited, set_vertex_visited, and reset_vertices_visited
    GraphAdjacencyList<int> graph;
    graph.add_vertex(1);
    graph.set_vertex_visited(1, true);
    if (!graph.vertex_visited(1)) {
        return false;
    }
    graph.set_vertex_visited(1, false);
    graph.add_vertex(2);
    graph.set_vertex_visited(2, true);
    if (!graph.vertex_visited(2) || graph.vertex_visited(1)) {
        return false;
    }
    graph.reset_vertices_visited();
    return !graph.vertex_visited(1) && !graph.vertex_visited(2);
}

bool test_GraphAdjacencyMatrix1() {
    // Test constructors, destructors, and assignment operators
    GraphAdjacencyMatrix<int> graph1;
    graph1.add_vertex(1);
    graph1.add_vertex(2);
    graph1.add_edge(1, 2);
    graph1.add_edge(2, 1);
    GraphAdjacencyMatrix<int> graph2{graph1};
    if (!graph2.adjacent(1, 2) || !graph2.adjacent(2, 1)) {
        return false;
    }
    const GraphAdjacencyMatrix<int> graph3{std::move(graph1)};
    if (!graph3.adjacent(1, 2) || !graph3.adjacent(2, 1)) {
        return false;
    }
    graph1 = graph2;
    if (!graph1.adjacent(1, 2) || !graph1.adjacent(2, 1)) {
        return false;
    }
    graph1 = std::move(graph2);
    return graph1.adjacent(1, 2) && graph1.adjacent(2, 1);
}

bool test_GraphAdjacencyMatrix2() {
    // Test add_vertex, remove_vertex, size, and empty
    GraphAdjacencyMatrix<int> graph;
    graph.add_vertex(1);
    graph.add_vertex(2);
    if (graph.size() != 2 || graph.empty()) {
        return false;
    }
    graph.remove_vertex(1);
    if (graph.size() != 1 || graph.empty()) {
        return false;
    }
    graph.add_vertex(3);
    if (graph.size() != 2 || graph.empty()) {
        return false;
    }
    graph.remove_vertex(2);
    if (graph.size() != 1 || graph.empty()) {
        return false;
    }
    graph.remove_vertex(3);
    return graph.empty();
}

bool test_GraphAdjacencyMatrix3() {
    // Test add_edge, remove_edge, and adjacent
    GraphAdjacencyMatrix<int> graph;
    graph.add_vertex(1);
    graph.add_vertex(2);
    graph.add_edge(1, 2);
    if (!graph.adjacent(1, 2) || graph.adjacent(2, 1)) { return false; }
    graph.add_edge(2, 1);
    if (!graph.adjacent(1, 2) || !graph.adjacent(2, 1)) { return false; }
    graph.remove_edge(1, 2);
    if (graph.adjacent(1, 2) || !graph.adjacent(2, 1)) { return false; }
    graph.remove_edge(2, 1);
    return !graph.adjacent(1, 2) && !graph.adjacent(2, 1);
}

bool test_GraphAdjacencyMatrix4() {
    // Test neighbours
    GraphAdjacencyMatrix<int> graph;
    graph.add_vertex(1);
    graph.add_vertex(2);
    graph.add_vertex(4);
    graph.add_edge(1, 2);
    graph.add_edge(2, 4);
    graph.add_edge(1, 4);
    auto neighbours1 = graph.neighbours(1);
    std::ranges::sort(neighbours1);
    const std::vector<int> expectedNeighbours1{2, 4};
    if (neighbours1 != expectedNeighbours1) {
        return false;
    }
    const auto neighbours2 = graph.neighbours(2);
    const std::vector<int> expectedNeighbours2{4};
    return neighbours2 == expectedNeighbours2;
}

bool test_GraphAdjacencyMatrix5() {
    // Test vertex_visited, set_vertex_visited, and reset_vertices_visited
    GraphAdjacencyMatrix<int> graph;
    graph.add_vertex(1);
    graph.set_vertex_visited(1, true);
    if (!graph.vertex_visited(1)) {
        return false;
    }
    graph.set_vertex_visited(1, false);
    graph.add_vertex(2);
    graph.set_vertex_visited(2, true);
    if (!graph.vertex_visited(2) || graph.vertex_visited(1)) {
        return false;
    }
    graph.reset_vertices_visited();
    return !graph.vertex_visited(1) && !graph.vertex_visited(2);
}

bool test_GraphIncidenceMatrix1() {
    // Test constructors, destructors, and assignment operators
    GraphIncidenceMatrix<int> graph1;
    graph1.add_vertex(1);
    graph1.add_vertex(2);
    graph1.add_edge(1, 2);
    graph1.add_edge(2, 1);
    GraphIncidenceMatrix<int> graph2{graph1};
    if (!graph2.adjacent(1, 2) || !graph2.adjacent(2, 1)) {
        return false;
    }
    const GraphIncidenceMatrix<int> graph3{std::move(graph1)};
    if (!graph3.adjacent(1, 2) || !graph3.adjacent(2, 1)) {
        return false;
    }
    graph1 = graph2;
    if (!graph1.adjacent(1, 2) || !graph1.adjacent(2, 1)) {
        return false;
    }
    graph1 = std::move(graph2);
    return graph1.adjacent(1, 2) && graph1.adjacent(2, 1);
}

bool test_GraphIncidenceMatrix2() {
    // Test add_vertex, remove_vertex, size, and empty
    GraphIncidenceMatrix<int> graph;
    graph.add_vertex(1);
    graph.add_vertex(2);
    if (graph.size() != 2 || graph.empty()) {
        return false;
    }
    graph.remove_vertex(1);
    if (graph.size() != 1 || graph.empty()) {
        return false;
    }
    graph.add_vertex(3);
    if (graph.size() != 2 || graph.empty()) {
        return false;
    }
    graph.remove_vertex(2);
    if (graph.size() != 1 || graph.empty()) {
        return false;
    }
    graph.remove_vertex(3);
    return graph.empty();
}

bool test_GraphIncidenceMatrix3() {
    // Test add_edge, remove_edge, and adjacent
    GraphIncidenceMatrix<int> graph;
    graph.add_vertex(1);
    graph.add_vertex(2);
    graph.add_edge(1, 2);
    if (!graph.adjacent(1, 2) || graph.adjacent(2, 1)) { return false; }
    graph.add_edge(2, 1);
    if (!graph.adjacent(1, 2) || !graph.adjacent(2, 1)) { return false; }
    graph.remove_edge(1, 2);
    if (graph.adjacent(1, 2) || !graph.adjacent(2, 1)) { return false; }
    graph.remove_edge(2, 1);
    return !graph.adjacent(1, 2) && !graph.adjacent(2, 1);
}

bool test_GraphIncidenceMatrix4() {
    // Test neighbours
    GraphIncidenceMatrix<int> graph;
    graph.add_vertex(1);
    graph.add_vertex(2);
    graph.add_vertex(4);
    graph.add_edge(1, 2);
    graph.add_edge(2, 4);
    graph.add_edge(1, 4);
    auto neighbours1 = graph.neighbours(1);
    std::ranges::sort(neighbours1);
    const std::vector<int> expectedNeighbours1{2, 4};
    if (neighbours1 != expectedNeighbours1) {
        return false;
    }
    const auto neighbours2 = graph.neighbours(2);
    const std::vector<int> expectedNeighbours2{4};
    return neighbours2 == expectedNeighbours2;
}

bool test_GraphIncidenceMatrix5() {
    // Test vertex_visited, set_vertex_visited, and reset_vertices_visited
    GraphIncidenceMatrix<int> graph;
    graph.add_vertex(1);
    graph.set_vertex_visited(1, true);
    if (!graph.vertex_visited(1)) {
        return false;
    }
    graph.set_vertex_visited(1, false);
    graph.add_vertex(2);
    graph.set_vertex_visited(2, true);
    if (!graph.vertex_visited(2) || graph.vertex_visited(1)) {
        return false;
    }
    graph.reset_vertices_visited();
    return !graph.vertex_visited(1) && !graph.vertex_visited(2);
}
