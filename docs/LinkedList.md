# LinkedList<T>

## Overview

`LinkedList<T>` is a singly linked list: a chain of heap-allocated `Node<T>`
objects, each pointing to the next. It supports insertion and removal at
either end, insertion relative to an existing key, and linear search.

## Features

- Header-only, templated on element type `T`
- Insertion at head, tail, or relative to an existing key
- Removal at head, tail, or by value
- `getHead()` exposes the raw node pointer so other containers (e.g.
  `HashMap`) can traverse buckets directly
- Deep-copying copy constructor and copy assignment operator

## Constructors

| Constructor | Description |
|---|---|
| `LinkedList()` | Creates an empty list. |
| `LinkedList(const LinkedList& other)` | Deep-copies `other`. |

## Public Methods

| Method | Description |
|---|---|
| `void insertAtHead(const T& val)` | Inserts `val` at the front. |
| `void insertAtTail(const T& val)` | Inserts `val` at the end. |
| `void insertBefore(const T& key, const T& val)` | Inserts `val` immediately before the first node equal to `key`. |
| `void insertAfter(const T& key, const T& val)` | Inserts `val` immediately after the first node equal to `key`. |
| `void removeAtHead()` | Removes the first element. |
| `void removeAtTail()` | Removes the last element. |
| `void remove(const T& val)` | Removes the first node equal to `val`, if any. |
| `bool search(const T& key) const` | Checks whether `key` exists in the list. |
| `void update(const T& key, const T& val)` | Replaces the value of the first node equal to `key`. |
| `std::size_t countNodes() const` | Number of elements currently stored. |
| `bool isEmpty() const` | `true` if the list has no elements. |
| `void display() const` | Prints the list's elements, space-separated. |
| `Node<T>* getHead() const` | Returns the raw head node pointer. |

## Time Complexity

| Operation | Complexity |
|---|---|
| `insertAtHead` | O(1) |
| `insertAtTail` | O(n) |
| `insertBefore` / `insertAfter` | O(n) |
| `removeAtHead` | O(1) |
| `removeAtTail` | O(n) |
| `remove` / `search` / `update` | O(n) |
| `countNodes` / `isEmpty` | O(1) |
| Copy construction / assignment | O(n) |

## Exceptions

| Method | Exception | Condition |
|---|---|---|
| `insertBefore` | `std::runtime_error` | List is empty, or `key` not found |
| `insertAfter` | `std::runtime_error` | `key` not found |
| `removeAtHead` | `std::underflow_error` | List is empty |
| `removeAtTail` | `std::underflow_error` | List is empty |
| `update` | `std::runtime_error` | `key` not found |

## Example

```cpp
#include "LinkedList.h"

LinkedList<int> list;

list.insertAtTail(10);
list.insertAtTail(20);
list.insertAtTail(30);

bool found = list.search(20); // true
list.remove(20);

try
{
    LinkedList<int> empty;
    empty.removeAtHead();
}
catch (const std::underflow_error& e)
{
    // handle empty list
}
```

## Notes

- Equality (used by `search`, `remove`, `update`, and the `key` parameters of
  `insertBefore`/`insertAfter`) relies on `T`'s `operator==`.
- `getHead()` is an intentional escape hatch for internal container
  composition (e.g. `HashMap` bucket traversal); general-purpose code should
  prefer the higher-level methods above it.
