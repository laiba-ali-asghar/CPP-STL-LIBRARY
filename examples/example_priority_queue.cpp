// Minimal usage example for PriorityQueue<T>.
// Run: g++ -std=c++17 -Iinclude examples/example_priority_queue.cpp -o example_pq

#include <iostream>
#include "PriorityQueue.h"

int main()
{
    // Create a priority queue
    PriorityQueue<int> pq;

    // Insert values
    pq.insert(5);
    pq.insert(15);
    pq.insert(10);

    // Read the max
    std::cout << "Max: " << pq.getMax() << std::endl; // 15

    // Extract values (largest first)
    std::cout << "Extracted: " << pq.extractMax() << std::endl; // 15
    std::cout << "Extracted: " << pq.extractMax() << std::endl; // 10
    std::cout << "Extracted: " << pq.extractMax() << std::endl; // 5

    // Handle an exception (extracting from an empty priority queue)
    try
    {
        pq.extractMax();
    }
    catch (const std::underflow_error& e)
    {
        std::cout << "Caught: " << e.what() << std::endl;
    }

    return 0;
}
