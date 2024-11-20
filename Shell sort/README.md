## Shell sort

**Shell sort** ("_Shellsort_" or "_Shell's method_"), is an in-place comparison sort.
It can be seen as either a generalization of sorting by exchange (_Bubble sort_)
or sorting by insertion (_Insertion sort_). The method starts by sorting pairs of
elements far apart from each other, then progressively reducing the gap between
elements to be compared. By starting with far-apart elements, it can move some
out-of-place elements into the position faster than a simple nearest-neighbor
exchange.

_Donald Shell_ published the first version of this sort in 1959.
The running time of _Shell sort_ is heavily dependent on the gap sequence it uses.
For many practical variants, determining their time complexity remains an open problem. 