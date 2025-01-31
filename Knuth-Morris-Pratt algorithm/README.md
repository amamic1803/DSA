## Knuth-Morris-Pratt algorithm

The **Knuth–Morris–Pratt algorithm** (or **KMP algorithm**) is a string-searching
algorithm that searches for occurrences of a "word" W within a main "text string" S
by employing the observation that when a mismatch occurs, the word itself embodies
sufficient information to determine where the next match could begin, thus bypassing
re-examination of previously matched characters.

The algorithm was conceived by _James H. Morris_ and independently discovered
by _Donald Knuth_ "a few weeks later" from automata theory.
_Morris_ and _Vaughan Pratt_ published a technical report in 1970.
The three also published the algorithm jointly in 1977.
Independently, in 1969, _Matiyasevich_ discovered a similar algorithm, coded by a
two-dimensional Turing machine, while studying a string-pattern-matching
recognition problem over a binary alphabet.
This was the first linear-time algorithm for string matching.
