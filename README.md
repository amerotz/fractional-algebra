# fractional-algebra
Simple C library for vector/matrix operations based on a fractional representation of numbers.

## Organization
This library is divided in three different parts: numbers, vectors, matrices.

### Numbers
Numbers are represented as fractions. Each operation involves the calculation of the Greatest Common Divisor and Least Square Multiple with the Euclidean Division algorithm. Fractions are always simplified.

### Vectors
Vectors are arrays of numbers. All operations allowed on numbers are extended as "bitwise" operations, plus "dot" multiplication and other vector shape/elements manipulation functions.

### Matrices
Matrices are array of vectors. Elementwise operations and manipulation functions are available, together with inverse matrix calculation, Gaussian Elimination and linear system solution (based on Gaussian Elimination).

## Safety
This library is NOT safe, meaning that there is no control over correct shape of vector/matrices, legality of operations etc. I may implement it in the future.
