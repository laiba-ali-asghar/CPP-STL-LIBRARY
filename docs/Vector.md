# Vector<T>

## Overview

`Vector<T>` is a dynamic array, similar in spirit to `std::vector`,
implemented from scratch. It automatically grows its underlying buffer
(doubling capacity) as elements are appended, and supports random access,
iteration, and bounds-checked access.

## Features

- Header-only, templated on element type `T`
- Automatic growth on `push_back` (doubling strategy)
- Bounds-checked access via `at()`, unchecked access via `operator[]`
- Minimal iterator support (`begin()`/`end()`) for range-based `for` and
  standard algorithms
- Deep-copying copy constructor and copy assignment operator

## Constructors

| Constructor | Description |
|---|---|
| `Vector()` | Creates an empty vector with no allocated storage. |
| `explicit Vector(std::size_t initialCapacity)` | Creates an empty vector with `initialCapacity` reserved up front. |
| `Vector(const Vector& other)` | Deep-copies `other`. |

## Public Methods

| Method | Description |
|---|---|
| `void push_back(const T& value)` | Appends `value`, growing the buffer if necessary. |
| `void pop_back()` | Removes the last element. |
| `T& at(std::size_t index)` | Bounds-checked access to the element at `index`. |
| `const T& at(std::size_t index) const` | Const bounds-checked access. |
| `T& operator[](std::size_t index)` | Unchecked access to the element at `index`. |
| `const T& operator[](std::size_t index) const` | Const unchecked access. |
| `T& front()` | Reference to the first element. |
| `T& back()` | Reference to the last element. |
| `std::size_t size() const` | Number of elements currently stored. |
| `std::size_t capacity() const` | Number of elements that fit without reallocating. |
| `bool empty() const` | `true` if the vector has no elements. |
| `void clear()` | Removes all elements without releasing the buffer. |
| `void reserve(std::size_t newCap)` | Ensures capacity is at least `newCap`. |
| `T* begin() / end()` | Iterators for range-based `for` and algorithms. |

## Time Complexity

| Operation | Complexity |
|---|---|
| `push_back` | Amortized O(1) |
| `pop_back` | O(1) |
| `at` / `operator[]` | O(1) |
| `front` / `back` | O(1) |
| `reserve` | O(n) if it triggers reallocation, otherwise O(1) |
| Copy construction / assignment | O(n) |

## Exceptions

| Method | Exception | Condition |
|---|---|---|
| `at` | `std::out_of_range` | `index >= size()` |
| `pop_back` | `std::underflow_error` | Vector is empty |
| `front` | `std::underflow_error` | Vector is empty |
| `back` | `std::underflow_error` | Vector is empty |

## Example

```cpp
#include "Vector.h"

Vector<int> vec;

vec.push_back(10);
vec.push_back(20);
vec.push_back(30);

int first = vec.front();  // 10
int atOne = vec.at(1);    // 20
vec.pop_back();

try
{
    vec.at(99);
}
catch (const std::out_of_range& e)
{
    // handle out-of-range access
}
```

## Notes

- `operator[]` performs no bounds checking; prefer `at()` when the index
  might be invalid.
- `reserve()` only grows capacity — it is a no-op if `newCap` is not larger
  than the current capacity.
- `clear()` resets the size to 0 but does not release allocated memory, so
  subsequent `push_back` calls can reuse the existing buffer.
