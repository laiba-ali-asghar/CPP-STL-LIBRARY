// Minimal usage example for Vector<T>.
// Run: g++ -std=c++17 -Iinclude examples/example_vector.cpp -o example_vector

#include <iostream>
#include "Vector.h"

int main()
{
    // Create a vector
    Vector<int> vec;

    // Push values
    vec.push_back(10);
    vec.push_back(20);
    vec.push_back(30);

    // Read values
    std::cout << "First: " << vec.front() << std::endl;    // 10
    std::cout << "Last: " << vec.back() << std::endl;      // 30
    std::cout << "At index 1: " << vec.at(1) << std::endl; // 20

    // Remove a value
    vec.pop_back();
    std::cout << "Size after pop_back: " << vec.size() << std::endl; // 2

    // Handle an exception (accessing an out-of-range index)
    try
    {
        vec.at(99);
    }
    catch (const std::out_of_range& e)
    {
        std::cout << "Caught: " << e.what() << std::endl;
    }

    return 0;
}
