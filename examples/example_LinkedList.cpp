// Minimal usage example for LinkedList<T>.
// Run: g++ -std=c++17 -Iinclude examples/example_linked_list.cpp -o example_linked_list

#include <iostream>
#include "LinkedList.h"

int main()
{
    // Create a list
    LinkedList<int> list;

    // Insert values
    list.insertAtTail(10);
    list.insertAtTail(20);
    list.insertAtTail(30);

    // Read (search)
    std::cout << "Contains 20? " << (list.search(20) ? "yes" : "no") << std::endl;

    // Remove a value
    list.remove(20);
    std::cout << "Count after remove: " << list.countNodes() << std::endl; // 2

    // Handle an exception (removing from head of an empty list)
    LinkedList<int> empty;
    try
    {
        empty.removeAtHead();
    }
    catch (const std::underflow_error& e)
    {
        std::cout << "Caught: " << e.what() << std::endl;
    }

    return 0;
}
