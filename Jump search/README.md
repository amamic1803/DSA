## Jump search

In computer science, a **jump search** or **block search** refers to a
search algorithm for ordered lists. It works by first checking all items
$L_{km}$, where $k ∈ \mathbb{N}$ and $m$ is the block size, until
an item is found that is larger than the search key. To find the exact
position of the search key in the list a linear search is performed
on the sublist $L[(k-1)m, km]$.

The optimal value of $m$ is $\sqrt n$, where $n$ is the length of the
list $L$. Because both steps of the algorithm look at, at most,
$\sqrt n$ items the algorithm runs in $O(\sqrt n)$ time.
This is better than a linear search, but worse than a binary search.
The advantage over the latter is that a jump search only needs to jump
backwards once, while a binary can jump backwards up to $\log (n)$ times.
This can be important if jumping backwards takes significantly more time
than jumping forwards.
