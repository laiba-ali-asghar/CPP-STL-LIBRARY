# Queue<T>

## Overview

`Queue<T>` is a circular-buffer First-In-First-Out (FIFO) container.
Elements are added at the rear via `enqueue()` and removed from the front
via `dequeue()`. Unlike `Stack`, `Queue` grows automatically (doubling its
buffer) when full, so callers don't need to pre-size it exactly.

## Features

- Header-only, templated on element type `T`
- Circular buffer avoids shifting elements on dequeue
- Automatic growth on `enqueue` when full
- Deep-copying copy constructor and copy assignment operator

## Constructors

| Constructor | Description |
|---|---|
| `Queue()` | Creates an empty queue with a default capacity of 10. |
| `explicit Queue(std::size_t cap)` | Creates an empty queue with capacity `cap`. Throws if `cap == 0`. |
| `Queue(const Queue& other)` | Deep-copies `other`. |

## Public Methods

| Method | Description |
|---|---|
| `void enqueue(const T& value)` | Adds `value` to the rear, growing the buffer if full. |
| `T dequeue()` | Removes and returns the element at the front. |
| `T& front()` | Reference to the element at the front. |
| `const T& front() const` | Const reference to the element at the front. |
| `std::size_t size() const` | Number of elements currently stored. |
| `bool isEmpty() const` | `true` if the queue has no elements. |
| `bool isFull() const` | `true` if the queue has reached its capacity. |

## Time Complexity

| Operation | Complexity |
|---|---|
| `enqueue` | Amortized O(1) |
| `dequeue` | O(1) |
| `front` | O(1) |
| `size` / `isEmpty` / `isFull` | O(1) |
| Copy construction / assignment | O(n) |

## Exceptions

| Method | Exception | Condition |
|---|---|---|
| `Queue(std::size_t cap)` | `std::invalid_argument` | `cap == 0` |
| `dequeue` | `std::underflow_error` | Queue is empty |
| `front` | `std::underflow_error` | Queue is empty |

## Example

```cpp
#include "Queue.h"

Queue<int> queue;

queue.enqueue(10);
queue.enqueue(20);
queue.enqueue(30);

int first = queue.front();  // 10
int removed = queue.dequeue(); // 10

try
{
    Queue<int> empty(2);
    empty.dequeue();
}
catch (const std::underflow_error& e)
{
    // handle empty queue
}
```

## Notes

- `isFull()` reflects the current buffer capacity, not a hard limit —
  `enqueue()` will transparently grow the buffer instead of throwing.
- Growth doubles the underlying capacity and relinearizes elements
  starting at index 0, so it costs O(n) on the calls where it happens.
