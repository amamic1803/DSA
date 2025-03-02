## Graph

In computer science, a **graph** is an abstract data type
meant to implement the undirected graph and
directed graph concepts from the field of graph theory
within mathematics.

A graph data structure consists of a finite
(and possibly mutable) set of vertices
(also called nodes or points), together with a set
of unordered pairs of these vertices for an
undirected graph or a set of ordered pairs for
a directed graph. These pairs are known as edges
(also called links or lines), and for a directed graph
are also known as edges but also sometimes arrows or arcs.
The vertices may be part of the graph structure or may be
external entities represented by integer indices or references.

A graph data structure may also associate with each edge
some edge value, such as a symbolic label or a numeric
attribute (cost, capacity, length, etc.).

The basic operations provided by a graph data structure G
usually include:
- _adjacent_(G, x, y): tests whether there is an edge from the vertex x to the vertex y;
- _neighbors_(G, x): lists all vertices y such that there is an edge from the vertex x to the vertex y;
- _add_vertex_(G, x): adds the vertex x, if it is not there;
- _remove_vertex_(G, x): removes the vertex x, if it is there;
- _add_edge_(G, x, y, z): adds the edge z from the vertex x to the vertex y, if it is not there;
- _remove_edge_(G, x, y): removes the edge from the vertex x to the vertex y, if it is there;
- _get_vertex_value_(G, x): returns the value associated with the vertex x;
- _set_vertex_value_(G, x, v): sets the value associated with the vertex x with v.

Structures that associate values with the edges usually also provide:
- _get_edge_value_(G, x, y): returns the value associated with the edge (x, y);
- _set_edge_value_(G, x, y, v): sets the value associated with the edge (x, y) to v.

Common data structures for graph representation:
- **Adjacency list**:
Vertices are stored as records or objects, and every
vertex stores a list of adjacent vertices. This data
structure allows the storage of additional data on the
vertices. Additional data can be stored if edges are
also stored as objects, in which case each vertex stores
its incident edges and each edge stores its incident
vertices.

- **Adjacency matrix**:
A two-dimensional matrix, in which the rows represent
source vertices and columns represent destination vertices.
Data on edges and vertices must be stored externally.
Only the cost for one edge can be stored between each pair
of vertices.

- **Incidence matrix**:
A two-dimensional matrix, in which the rows represent
the vertices and columns represent the edges.
The entries indicate the incidence relation between
the vertex at a row and edge at a column.
