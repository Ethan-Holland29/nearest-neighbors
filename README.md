// ============================================================
// Nearest-Neighbor Ranking & Lookup Tool
// Ethan Holland — 9/17/2026
// ============================================================

// This is a nearest-neighbor ranking and lookup tool. Given a location
// and a set of points, it ranks the points by proximity using a tuned
// hybrid sorting algorithm (merge sort that cuts off to insertion sort
// for small partitions) and supports an efficient O(log n) runtime when
// ranking each lookup via binary search.

// ------------------------------------------------------------
// How It Works
// ------------------------------------------------------------

// 1. Distance calculation
//    Each point's Euclidean distance from a given reference location
//    is computed.

// 2. Hybrid sort
//    Points are sorted by distance (nearest first, ties broken by x
//    then y) using merge sort, which switches to insertion sort once
//    a subarray shrinks to a configurable threshold t. This avoids
//    merge sort's overhead on small partitions, similar to the
//    approach used in production sorting algorithms like Timsort.

// 3. Binary search lookup
//    Once sorted, any query point can be located in O(log n) time,
//    returning its rank (1st closest, 2nd closest, etc.) or reporting
//    that it isn't in the set.

// ------------------------------------------------------------
// Input Format
// ------------------------------------------------------------

//   x y n s t
//
//   x y  - the reference location's coordinates
//   n    - number of points to rank
//   s    - number of query points to look up
//   t    - size threshold for switching from merge sort to insertion sort
//
// Followed by:
//   n lines of "x y" - the points to be ranked
//   s lines of "x y" - the points to search for

// ------------------------------------------------------------
// Output
// ------------------------------------------------------------

//   The n points, printed in order of increasing distance from the
//   reference location.
//
//   For each of the s query points, either:
//     x y found at rank k
//     x y not found

// ------------------------------------------------------------
// Build & Run
// ------------------------------------------------------------

//   gcc -o nn_lookup main.c -lm
//   ./nn_lookup < input.txt

// ------------------------------------------------------------
// Example
// ------------------------------------------------------------

// Input:
//   0 0 4 2 2
//   1 1
//   3 3
//   0 2
//   5 5
//   1 1
//   2 2
//
// Output:
//   0 2
//   1 1
//   3 3
//   5 5
//   1 1 found at rank 2
//   2 2 not found
