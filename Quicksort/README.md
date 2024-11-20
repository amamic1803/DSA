## Quicksort

**Quicksort** is an efficient, general-purpose sorting algorithm.
It was developed by British computer scientist _Tony Hoare_ in 1959 and published in 1961.
It is still a commonly used algorithm for sorting.
Overall, it is slightly faster than _merge sort_ and _heapsort_ for randomized data,
particularly on larger distributions.

_Quicksort_ is a divide-and-conquer algorithm.
It works by selecting a 'pivot' element from the array and partitioning the other elements into
two sub-arrays, according to whether they are less than or greater than the pivot.
For this reason, it is sometimes called partition-exchange sort.
The sub-arrays are then sorted recursively. This can be done in-place, requiring small additional amounts
of memory to perform the sorting.

_Quicksort_ is a comparison sort, meaning that it can sort items of any type for which a "less-than"
relation (formally, a total order) is defined.
It is a comparison-based sort since elements a and b are only swapped in case their relative order
has been obtained in the transitive closure of prior comparison-outcomes.
Most implementations of _quicksort_ are not stable, meaning that the relative order of equal sort items
is not preserved.

Mathematical analysis of _quicksort_ shows that, on average, the algorithm takes $O(n \log n)$ comparisons
to sort $n$ items. In the worst case, it makes $O(n^2)$ comparisons.
