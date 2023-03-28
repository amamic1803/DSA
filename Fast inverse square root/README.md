## Fast inverse square root

**Fast inverse square root** (**Fast InvSqrt()**, **0x5F3759DF**),
is an algorithm that estimates $\frac {1} {\sqrt {x}}$.
This operation is used in digital signal processing to normalize a vector,
such as scaling it to length 1.
For example, computer graphics programs use inverse square roots to compute angles of incidence
and reflection for lighting and shading.
Predated by similar video game algorithms, this one is best known for its implementation in 1999
in Quake III Arena, a first-person shooter video game heavily based on 3D graphics.
Computation of square roots usually depends upon many division operations,
which for floating point numbers are computationally expensive.
The fast inverse square generates a good approximation with only one division step.
