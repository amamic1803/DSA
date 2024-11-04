## Insertion sort

**Insertion sort** is a simple sorting algorithm that builds
the final sorted array (or list) one item at a time by comparisons.
It is much less efficient on large lists than more advanced algorithms
such as quicksort, heapsort, or merge sort.

However, insertion sort provides several advantages:
- _simple_: easy to implement
- _efficient_: for (quite) small data sets, much like other quadratic $O(n^2)$ sorting algorithms
- _more efficient_: than most other simple quadratic algorithms such as selection sort or bubble sort
- _adaptive_: efficient for data sets that are already substantially sorted
- _stable_: does not change the relative order of elements with equal keys
- _in-place_: only requires a constant amount $O(1)$ of additional memory space
- _online_: can sort a list as it receives it
