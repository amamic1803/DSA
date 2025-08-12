## Merge sort

**Merge sort** (also "_mergesort_" and "_merge-sort_") is an efficient,
general-purpose, and comparison-based sorting algorithm.
Most implementations produce a stable sort, which means that the relative order
of equal elements is the same in the input and output. Merge sort is a
divide-and-conquer algorithm invented by _John von Neumann_ in 1945.
A detailed description and analysis of the bottom-up merge sort appeared in a report
by _Goldstine_ and _von Neumann_ as early as 1948.

Conceptually, a _merge sort_ works as follows:
1. Divide the unsorted list into $n$ sublists, each containing one element (a list of one element is considered sorted).
2. Repeatedly merge sublists to produce new sorted sublists until there is only one sublist remaining. This will be the sorted list.