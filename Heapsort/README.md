## Heapsort

**Heapsort** is a comparison-based sorting algorithm which can be thought of as
"an implementation of selection sort using the right data structure."
Like selection sort, heapsort divides its input into a sorted and an unsorted region,
and it iteratively shrinks the unsorted region by extracting the largest element from it
and inserting it into the sorted region. Unlike selection sort, heapsort does not waste
time with a linear-time scan of the unsorted region; rather, heap sort maintains
the unsorted region in a heap data structure to efficiently find the largest element
in each step.

Although somewhat slower in practice on most machines than a well-implemented quicksort,
it has the advantages of very simple implementation and a more favorable worst-case
$O(n \log n)$ runtime. Most real-world quicksort variants include an implementation
of heapsort as a fallback should they detect that quicksort is becoming degenerate.
Heapsort is an in-place algorithm, but it is not a stable sort.

Heapsort was invented by J. W. J. Williams in 1964.
The paper also introduced the binary heap as a useful data structure in its own right.
In the same year, Robert W. Floyd published an improved version that could sort an array
in-place, continuing his earlier research into the treesort algorithm.
