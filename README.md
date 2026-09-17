# Nearest-Neighbor Ranking & Lookup Tool
**Ethan Holland — 9/17/2026**

Ranks a set of points by distance from a reference location and supports fast rank lookups, using a hybrid merge/insertion sort and binary search.

## How It Works
1. Computes each point's Euclidean distance from the reference location.
2. Sorts points by distance using merge sort, which switches to insertion sort below a threshold `t` (like Timsort's small-array optimization).
3. Binary searches the sorted list to find a query point's rank in O(log n).

## Input
`x y` = reference point, `n` = points to rank, `s` = points to look up, `t` = sort threshold.

Then `n` lines of `x y` (points to rank), then `s` lines of `x y` (points to search for).

## Output
- All `n` points, sorted by distance (nearest first)
- For each query: `x y found at rank k` or `x y not found`

## Build & Run
```bash
gcc -o nn_lookup main.c -lm
./nn_lookup < input.txt
```

## Example
**Input:**
0 0 4 2 2
1 1
3 3
0 2
5 5
1 1
2 2

**Output:**
0 2
1 1
3 3
5 5
1 1 found at rank 2
2 2 not found
