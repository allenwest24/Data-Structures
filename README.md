# Data-Structures
Sorting with Vectors and Hashmaps

Part 1: Vectors

Implementing the “svec” data structure and the “sort” function. Used gnome sort.

    length-sort: Sort the provided input file by string length, shortest to longest and print the result to stdout.

Part 2: Hash Maps

Implementing the “hashmap” data structure.

This hashmap uses the "linear probing" strategy for collisions, and has a hash function that avoids excess collisions.

    top-triples: Find the top N letter triples occuring in words in the input, print the counts and triples to stdout.

Example input:

abcd
bcde
cdef

Example session:

$ ./top-triples input 2
2   bcd
2   cde
