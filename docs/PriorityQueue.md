# PriorityQueue<T>

## Overview

`PriorityQueue<T>` is a binary max-heap, backed by a dynamically growing
array. The largest element (by `operator<`) is always accessible in O(1)
via `getMax()`, and can be removed in O(log n) via `extractMax()`.

## Features

- Header-only, templated on element type `T` (requires `operator<` and `operator>`)
- Array-backed binary heap with automatic growth
- `deleteKey()` and `increaseKey()` for arbitrary-index heap manipulation
- Deep-copying copy constructor and copy assignment operator

## Constructors

| Constructor | Description |
|---|---|
| `PriorityQueue()` | Creates an empty priority queue with a default capacity of 10. |
| `explicit PriorityQueue(std::size_t cap)` | Creates an empty priority queue with capacity `cap` (0 is treated as 1). |
| `PriorityQueue(const PriorityQueue& other)` | Deep-copies `other`. |

## Public Methods

| Method | Description |
|---|---|
| `void insert(const T& key)` | Inserts `key`, growing the buffer if necessary. |
| `T extractMax()` | Removes and returns the maximum element. |
| `const T& getMax() const` | Returns the maximum element without removing it. |
| `void deleteKey(std::size_t i)` | Removes the element at heap index `i`. |
| `void increaseKey(std::size_t i, const T& newValue)` | Increases the value at index `i` to `newValue`. |
| `std::size_t size() const` | Number of elements currently stored. |
| `bool isEmpty() const` | `true` if the priority queue has no elements. |
| `void display() const` | Prints the heap's underlying array (heap order, not sorted order). |

## Time Complexity

| Operation | Complexity |
|---|---|
| `insert` | Amortized O(log n) |
| `extractMax` | O(log n) |
| `getMax` | O(1) |
| `deleteKey` | O(log n) |
| `increaseKey` | O(log n) |
| `size` / `isEmpty` | O(1) |
| Copy construction / assignment | O(n) |

## Exceptions

| Method | Exception | Condition |
|---|---|---|
| `extractMax` | `std::underflow_error` | Priority queue is empty |
| `getMax` | `std::underflow_error` | Priority queue is empty |
| `deleteKey` | `std::out_of_range` | `i` is not a valid index |
| `increaseKey` | `std::out_of_range` | `i` is not a valid index |
| `increaseKey` | `std::invalid_argument` | `newValue` is smaller than the current value |

## Example

```cpp
#include "PriorityQueue.h"

PriorityQueue<int> pq;

pq.insert(5);
pq.insert(15);
pq.insert(10);

int max = pq.getMax();     // 15
int removed = pq.extractMax(); // 15

try
{
    PriorityQueue<int> empty;
    empty.extractMax();
}
catch (const std::underflow_error& e)
{
    // handle empty priority queue
}
```

## Notes

- `display()` prints the heap's internal array order, which reflects the
  heap invariant, not a fully sorted sequence.
- `deleteKey()` re-heapifies in whichever direction is needed after
  replacing the removed slot — sifting down alone is not always sufficient,
  since the replacement value may be larger than its new parent.
- `increaseKey()` only allows increasing a value; passing a smaller
  `newValue` throws rather than silently decreasing it.
