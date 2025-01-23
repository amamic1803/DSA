## Rabin-Karp algorithm

The **Rabin–Karp algorithm** or **Karp–Rabin algorithm** is a string-searching
algorithm created by _Richard M. Karp_ and _Michael O. Rabin_ (1987) that uses
hashing to find an exact match of a pattern string in a text. It uses a rolling
hash to quickly filter out positions of the text that cannot match the pattern,
and then checks for a match at the remaining positions. Generalizations of the
same idea can be used to find more than one match of a single pattern, or to
find matches for more than one pattern.

To find a single match of a single pattern, the expected time of the algorithm
is linear in the combined length of the pattern and text, although its
worst-case time complexity is the product of the two lengths. To find
multiple matches, the expected time is linear in the input lengths, plus 
the combined length of all the matches, which could be greater than linear.
