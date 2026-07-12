// Minimal usage example for HashMap<K, V>.
// Run: g++ -std=c++17 -Iinclude examples/example_hash_map.cpp -o example_hash_map

#include <iostream>
#include "HashMap.h"

int main()
{
    // Create a map
    HashMap<std::string, int> map;

    // Insert values
    map.insert("apple", 3);
    map.insert("banana", 5);

    // Read a value
    int value = 0;
    if (map.get("apple", value))
    {
        std::cout << "apple: " << value << std::endl; // 3
    }

    // Remove a value
    map.remove("banana");
    std::cout << "Contains banana? " << (map.contains("banana") ? "yes" : "no") << std::endl;

    // HashMap reports a missing key by returning false rather than
    // throwing, so check the result instead of catching an exception.
    if (!map.get("missing", value))
    {
        std::cout << "'missing' not found - handled without an exception" << std::endl;
    }

    return 0;
}
