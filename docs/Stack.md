# Stack<T>

## Overview

`Stack<T>` is a fixed-capacity, array-based Last-In-First-Out (LIFO)
container. Elements are pushed and popped from the same end (the "top").
Unlike `Vector`, it does not grow automatically — once its capacity is
reached, `push()` throws instead of reallocating.

## Features

- Header-only, templated on element type `T`
- Fixed capacity, set at construction time
- O(1) push, pop, and top access
- Deep-copying copy constructor and copy assignment operator
- Exception-based error handling for invalid state (empty/full)

## Constructors

| Constructor | Description |
|---|---|
| `Stack()` | Creates an empty stack with a default capacity of 10. |
| `explicit Stack(std::size_t cap)` | Creates an empty stack with capacity `cap`. Throws if `cap == 0`. |
| `Stack(const Stack& other)` | Deep-copies `other`. |

## Public Methods

| Method | Description |
|---|---|
| `void push(const T& value)` | Pushes `value` onto the top of the stack. |
| `T pop()` | Removes and returns the top element. |
| `T& stackTop()` | Returns a reference to the top element. |
| `const T& stackTop() const` | Returns a const reference to the top element. |
| `std::size_t size() const` | Returns the number of elements currently stored. |
| `bool isEmpty() const` | Returns `true` if the stack has no elements. |
| `bool isFull() const` | Returns `true` if the stack has reached its capacity. |

## Time Complexity

| Operation | Complexity |
|---|---|
| `push` | O(1) |
| `pop` | O(1) |
| `stackTop` | O(1) |
| `size` / `isEmpty` / `isFull` | O(1) |
| Copy construction / assignment | O(n) |

## Exceptions

| Method | Exception | Condition |
|---|---|---|
| `Stack(std::size_t cap)` | `std::invalid_argument` | `cap == 0` |
| `push` | `std::overflow_error` | Stack is full |
| `pop` | `std::underflow_error` | Stack is empty |
| `stackTop` | `std::underflow_error` | Stack is empty |

## Example

```cpp
#include "Stack.h"

Stack<int> stack;

stack.push(10);
stack.push(20);
stack.push(30);

int top = stack.stackTop(); // 30
int popped = stack.pop();   // 30

try
{
    Stack<int> empty(1);
    empty.pop();
}
catch (const std::underflow_error& e)
{
    // handle empty stack
}
```

## Notes

- Capacity is fixed at construction time; `Stack` does not support
  `reserve()` or automatic growth. If unbounded growth is needed, use
  `Vector<T>` and treat its back as the top instead.
- `stackTop()` has both a mutable and a `const` overload, so it works on
  both mutable and read-only stacks.
