# DoublyLinkedList<T>

## Overview

`DoublyLinkedList<T>` is a **circular** doubly linked list. Each node has a
`next` and a `prev` pointer, and `head->prev` always points to the tail, so
both ends are reachable in O(1) without a separate tail pointer.

## Features

- Header-only, templated on element type `T`
- Circular structure gives O(1) access to both head and tail
- Insertion and removal at either end, and removal by value
- Deep-copying copy constructor and copy assignment operator

## Constructors

| Constructor | Description |
|---|---|
| `DoublyLinkedList()` | Creates an empty list. |
| `DoublyLinkedList(const DoublyLinkedList& other)` | Deep-copies `other`. |

## Public Methods

| Method | Description |
|---|---|
| `void clear()` | Removes all elements. |
| `void insertAtHead(const T& val)` | Inserts `val` at the front. |
| `void insertAtTail(const T& val)` | Inserts `val` at the end. |
| `void removeAtHead()` | Removes the first element. |
| `void removeAtTail()` | Removes the last element. |
| `void remove(const T& val)` | Removes the first node equal to `val`, if any. |
| `bool search(const T& key) const` | Checks whether `key` exists in the list. |
| `void update(const T& key, const T& val)` | Replaces the value of the first node equal to `key`. |
| `std::size_t countNodes() const` | Number of elements currently stored. |
| `bool isEmpty() const` | `true` if the list has no elements. |
| `void display() const` | Prints the list's elements, space-separated. |

## Time Complexity

| Operation | Complexity |
|---|---|
| `insertAtHead` / `insertAtTail` | O(1) |
| `removeAtHead` / `removeAtTail` | O(1) |
| `remove` / `search` / `update` | O(n) |
| `countNodes` / `isEmpty` | O(1) |
| `clear` | O(n) |
| Copy construction / assignment | O(n) |

## Exceptions

| Method | Exception | Condition |
|---|---|---|
| `removeAtHead` | `std::underflow_error` | List is empty |
| `removeAtTail` | `std::underflow_error` | List is empty |
| `update` | `std::runtime_error` | List is empty, or `key` not found |

## Example

```cpp
#include "DoublyLinkedList.h"

DoublyLinkedList<int> list;

list.insertAtHead(10);
list.insertAtTail(20);
list.insertAtTail(30);

bool found = list.search(20); // true
list.remove(20);

try
{
    DoublyLinkedList<int> empty;
    empty.removeAtHead();
}
catch (const std::underflow_error& e)
{
    // handle empty list
}
```

## Notes

- Because the list is circular, traversals that walk the whole list use a
  do/while loop that stops when it returns to `head`, rather than checking
  for `nullptr`.
- Equality (used by `search`, `remove`, and the `key` parameter of `update`)
  relies on `T`'s `operator==`.
