// Minimal usage example for Queue<T>.
// Run: g++ -std=c++17 -Iinclude examples/example_queue.cpp -o example_queue

#include <iostream>
#include "Queue.h"

int main()
{
    // Create a queue
    Queue<int> queue;

    // Enqueue values
    queue.enqueue(10);
    queue.enqueue(20);
    queue.enqueue(30);

    // Read the front
    std::cout << "Front: " << queue.front() << std::endl; // 10

    // Dequeue values
    std::cout << "Dequeued: " << queue.dequeue() << std::endl; // 10
    std::cout << "Dequeued: " << queue.dequeue() << std::endl; // 20
    std::cout << "Dequeued: " << queue.dequeue() << std::endl; // 30

    // Handle an exception (dequeuing an empty queue)
    try
    {
        queue.dequeue();
    }
    catch (const std::underflow_error& e)
    {
        std::cout << "Caught: " << e.what() << std::endl;
    }

    return 0;
}
