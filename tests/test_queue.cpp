// Behavior tests for Queue<T>. Exceptions are covered separately in
// test_queue_exceptions.cpp.
#include <cassert>
#include "../include/Queue.h"

int main()
{
    Queue<int> q(3);
    assert(q.isEmpty());

    q.enqueue(1);
    q.enqueue(2);
    assert(q.size() == 2);
    assert(q.front() == 1);

    assert(q.dequeue() == 1);
    assert(q.size() == 1);
    assert(q.front() == 2);

    q.enqueue(3);
    q.enqueue(4);
    assert(q.isFull()); // size == capacity (3)

    // Automatic growth: enqueue past the initial capacity.
    for (int i = 5; i <= 10; ++i)
    {
        q.enqueue(i);
    }
    assert(q.size() == 9);
    assert(q.front() == 2);

    // FIFO order is preserved through wraparound and growth.
    int expected = 2;
    while (!q.isEmpty())
    {
        assert(q.dequeue() == expected);
        ++expected;
    }
    assert(expected == 11);

    // Copy constructor produces an independent queue.
    Queue<int> original(4);
    original.enqueue(100);
    original.enqueue(200);
    Queue<int> copy(original);
    copy.dequeue();
    assert(original.size() == 2);
    assert(copy.size() == 1);

    return 0;
}
