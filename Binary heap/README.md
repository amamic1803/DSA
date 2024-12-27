## Binary heap

A **binary heap** is a heap data structure that takes the form of a binary tree.
Binary heaps are a common way of implementing priority queues.
The binary heap was introduced by J. W. J. Williams in 1964 as a data structure for implementing heapsort.

A binary heap is defined as a binary tree with two additional constraints:
1. Shape property: a binary heap is a complete binary tree; that is, all levels of the tree, except possibly the last one (deepest) are fully filled, and, if the last level of the tree is not complete, the nodes of that level are filled from left to right.
2. Heap property: the key stored in each node is either greater than or equal to (≥) or less than or equal to (≤) the keys in the node's children, according to some total order.

Heaps where the parent key is greater than or equal to (≥) the child keys
are called max-heaps; those where it is less than or equal to (≤) are called min-heaps.
Efficient (that is, logarithmic time) algorithms are known for the two operations
needed to implement a priority queue on a binary heap:
1. Inserting an element.
2. Removing the smallest or largest element from (respectively) a min-heap or max-heap.

Binary heaps are also commonly employed in the heapsort sorting algorithm,
which is an in-place algorithm because binary heaps can be implemented as an implicit
data structure, storing keys in an array and using their relative positions within
that array to represent child–parent relationships.
