// Exception-only tests for PriorityQueue<T>. Behavior tests live in
// test_priority_queue.cpp.
#include <cassert>
#include "../include/PriorityQueue.h"

int main()
{
    // extractMax() throws when empty.
    {
        bool thrown = false;
        PriorityQueue<int> empty;
        try
        {
            empty.extractMax();
        }
        catch (const std::underflow_error&)
        {
            thrown = true;
        }
        assert(thrown);
    }

    // getMax() throws when empty.
    {
        bool thrown = false;
        PriorityQueue<int> empty;
        try
        {
            empty.getMax();
        }
        catch (const std::underflow_error&)
        {
            thrown = true;
        }
        assert(thrown);
    }

    // deleteKey() throws for an out-of-range index.
    {
        bool thrown = false;
        PriorityQueue<int> pq;
        pq.insert(1);
        try
        {
            pq.deleteKey(99);
        }
        catch (const std::out_of_range&)
        {
            thrown = true;
        }
        assert(thrown);
    }

    // increaseKey() throws for an out-of-range index.
    {
        bool thrown = false;
        PriorityQueue<int> pq;
        pq.insert(1);
        try
        {
            pq.increaseKey(99, 5);
        }
        catch (const std::out_of_range&)
        {
            thrown = true;
        }
        assert(thrown);
    }

    // increaseKey() throws when the new value is smaller than the current one.
    {
        bool thrown = false;
        PriorityQueue<int> pq;
        pq.insert(10);
        try
        {
            pq.increaseKey(0, 1);
        }
        catch (const std::invalid_argument&)
        {
            thrown = true;
        }
        assert(thrown);
    }

    return 0;
}
