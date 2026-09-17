Ethan Holland 9/17/2026
this is a nearest neighbor ranking and lookup tool. 
Given a location and a set of points, it ranks the points by proximity using a tuned hybrid sorting algorithm (merge sort that cuts off to insertion sort for small partitions) and supports an efficient O(log n) runtime when ranking each lookup via binary search.
