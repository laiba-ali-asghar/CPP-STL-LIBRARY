# HashMap<K, V>

## Overview

`HashMap<K, V>` is a separate-chaining hash map: an array of `LinkedList`
buckets, indexed by `std::hash<K>`. It automatically rehashes (doubling the
bucket count) once the load factor exceeds 0.75.

## Features

- Header-only, templated on key type `K` (must work with `std::hash` and
  `operator==`) and value type `V`
- Separate chaining via `LinkedList<Pair<K, V>>` buckets
- Automatic rehashing to keep the load factor bounded
- `operator[]` for map-style access and insertion
- `keys()` / `values()` for collecting all entries
- Deep-copying copy constructor and copy assignment operator

## Constructors

| Constructor | Description |
|---|---|
| `explicit HashMap(std::size_t cap = 10)` | Creates an empty map with `cap` buckets (0 is treated as 1). |
| `HashMap(const HashMap& other)` | Deep-copies `other`. |

## Public Methods

| Method | Description |
|---|---|
| `void insert(const K& key, const V& value)` | Inserts or updates the value for `key`. |
| `bool get(const K& key, V& value) const` | Looks up `key`; copies the value into `value` and returns `true` if found. |
| `bool contains(const K& key) const` | Checks whether `key` exists. |
| `bool remove(const K& key)` | Removes the entry for `key`, if present. |
| `void clear()` | Removes all entries. |
| `LinkedList<K> keys() const` | Returns all keys, in bucket-traversal order. |
| `LinkedList<V> values() const` | Returns all values, in bucket-traversal order. |
| `std::size_t size() const` | Number of entries currently stored. |
| `double loadFactor() const` | Current load factor (`size() / bucket count`). |
| `bool isEmpty() const` | `true` if the map has no entries. |
| `void display() const` | Prints each bucket's contents, one bucket per line. |
| `V& operator[](const K& key)` | Returns a reference to `key`'s value, inserting a default value if absent. |

## Time Complexity

| Operation | Complexity |
|---|---|
| `insert` | Amortized O(1) |
| `get` / `contains` / `remove` | O(1) average, O(n) worst case (heavy collisions) |
| `operator[]` | O(1) average, O(n) worst case |
| `clear` | O(n) |
| `keys` / `values` | O(n) |
| Copy construction / assignment | O(n) |

## Exceptions

`HashMap` does not throw for ordinary usage; missing keys are reported
through return values instead:

- `get()` returns `false` if the key is not found.
- `contains()` returns `false` if the key is not found.
- `remove()` returns `false` if the key is not found.

The only exception it can throw is an internal `std::runtime_error` from
`operator[]` if an invariant is violated after insertion; this should not
occur under normal use and is not part of the public contract to catch.

## Example

```cpp
#include "HashMap.h"

HashMap<std::string, int> map;

map.insert("apple", 3);
map.insert("banana", 5);

int value = 0;
if (map.get("apple", value))
{
    // value == 3
}

map.remove("banana");

if (!map.get("missing", value))
{
    // key not found - handled without an exception
}
```

## Notes

- `K` must be hashable with `std::hash<K>` and comparable with `operator==`.
- Iteration order (via `display()`, `keys()`, `values()`) follows bucket
  index and, within a bucket, most-recently-inserted-first — it is not
  insertion order across the whole map and is not guaranteed to be stable
  across a rehash.
- `operator[]` inserts a default-constructed `V` if `key` is absent, the
  same way `std::map::operator[]` does — use `get()` or `contains()` if you
  want a lookup that never inserts.
