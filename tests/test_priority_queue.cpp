// Behavior tests for PriorityQueue<T>. Exceptions are covered separately in
// test_priority_queue_exceptions.cpp.
#include <cassert>
#include "../include/PriorityQueue.h"

int main()
{
    PriorityQueue<int> pq;
    assert(pq.isEmpty());

    for (int v : {3, 2, 15, 5, 4, 45})
    {
        pq.insert(v);
    }
    assert(pq.size() == 6);
    assert(pq.getMax() == 45);

    assert(pq.extractMax() == 45);
    assert(pq.size() == 5);
    assert(pq.getMax() == 15);

    // deleteKey exercises the sift-up-or-down fix: the value that replaces
    // the deleted slot may need to move in either direction.
    pq.deleteKey(1);
    assert(pq.size() == 4);

    // Extracting the rest returns values in descending order.
    int previous = pq.extractMax();
    while (!pq.isEmpty())
    {
        int next = pq.extractMax();
        assert(next <= previous);
        previous = next;
    }

    // increaseKey raises a value and restores heap order.
    PriorityQueue<int> pq2;
    pq2.insert(10);
    pq2.insert(20);
    pq2.insert(5);
    pq2.increaseKey(2, 100); // index 2 holds 5 in the array before this call
    assert(pq2.getMax() == 100);

    return 0;
}
