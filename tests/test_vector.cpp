// Behavior tests for Vector<T>. Exceptions are covered separately in
// test_vector_exceptions.cpp.
#include <cassert>
#include "../include/Vector.h"

int main()
{
    Vector<int> v;
    assert(v.empty());
    assert(v.size() == 0);

    for (int i = 1; i <= 5; ++i)
    {
        v.push_back(i * 10);
    }

    assert(v.size() == 5);
    assert(v.front() == 10);
    assert(v.back() == 50);
    assert(v.at(2) == 30);
    assert(v[2] == 30);

    v.pop_back();
    assert(v.size() == 4);
    assert(v.back() == 40);

    v.reserve(100);
    assert(v.capacity() >= 100);
    assert(v.size() == 4); // reserve does not change size

    // Iterators visit elements in order.
    int expected[] = {10, 20, 30, 40};
    int i = 0;
    for (const auto& x : v)
    {
        assert(x == expected[i]);
        ++i;
    }
    assert(i == 4);

    v.clear();
    assert(v.empty());
    assert(v.size() == 0);

    // Copy constructor produces an independent vector.
    Vector<int> original;
    original.push_back(1);
    original.push_back(2);
    Vector<int> copy = original;
    copy.push_back(3);
    assert(original.size() == 2);
    assert(copy.size() == 3);

    return 0;
}
