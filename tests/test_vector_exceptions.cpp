// Exception-only tests for Vector<T>. Behavior tests live in test_vector.cpp.
#include <cassert>
#include "../include/Vector.h"

int main()
{
    // at() throws when the index is out of range.
    {
        bool thrown = false;
        Vector<int> v;
        v.push_back(1);
        try
        {
            v.at(100);
        }
        catch (const std::out_of_range&)
        {
            thrown = true;
        }
        assert(thrown);
    }

    // pop_back() throws when the vector is empty.
    {
        bool thrown = false;
        Vector<int> v;
        try
        {
            v.pop_back();
        }
        catch (const std::underflow_error&)
        {
            thrown = true;
        }
        assert(thrown);
    }

    // front() throws when the vector is empty.
    {
        bool thrown = false;
        Vector<int> v;
        try
        {
            v.front();
        }
        catch (const std::underflow_error&)
        {
            thrown = true;
        }
        assert(thrown);
    }

    // back() throws when the vector is empty.
    {
        bool thrown = false;
        Vector<int> v;
        try
        {
            v.back();
        }
        catch (const std::underflow_error&)
        {
            thrown = true;
        }
        assert(thrown);
    }

    return 0;
}
