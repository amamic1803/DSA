## Chinese remainder theorem

The **Chinese remainder theorem** is a theorem that describes the integer solutions to systems of simultaneous congruences.
The theorem is named after the Chinese mathematician Sun Zi, who lived around 3rd century AD.

If one knows the remainders of the Euclidean division of an integer n by several integers,
then one can uniquely determine the remainder of the division of n by the least common multiple of these integers.

Example:
```
x ≡ 2 (mod 3)
x ≡ 3 (mod 5)
x ≡ 2 (mod 7)
```
The solution to this system of congruences is ```x = 23```.
Other solutions are ```x = 23 + 105k```, where k is an integer.
That is because 105 is the least common multiple of 3, 5 and 7.
