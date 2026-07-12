#pragma once

#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <utility> // std::swap only - not a container

/**
 * @brief Binary max-heap based priority queue.
 *
 * The largest element (by operator<) is always accessible in O(1) via
 * getMax(), and can be removed in O(log n) via extractMax().
 *
 * @tparam T Type of element stored in the priority queue. Must support
 * operator< and operator>.
 */
template <typename T>
class PriorityQueue
{
private:
    T* data;
    std::size_t count;
    std::size_t capacity;

    /**
     * @brief Doubles the underlying buffer's capacity, copying existing
     * elements over.
     */
    void resize()
    {
        std::size_t newCap = capacity * 2;
        T* newData = new T[newCap];
        for (std::size_t i = 0; i < count; ++i)
        {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
        capacity = newCap;
    }

    /**
     * @brief Restores the max-heap property by moving the element at index
     * @p i upward until its parent is no smaller.
     *
     * @param i Index of the element to sift up.
     */
    void siftUp(std::size_t i)
    {
        while (i != 0)
        {
            std::size_t parent = (i - 1) / 2;
            if (data[parent] < data[i])
            {
                std::swap(data[parent], data[i]);
                i = parent;
            }
            else
            {
                break;
            }
        }
    }

    /**
     * @brief Restores the max-heap property by moving the element at index
     * @p i downward until both children are no larger.
     *
     * @param i Index of the element to sift down.
     */
    void siftDown(std::size_t i)
    {
        while (true)
        {
            std::size_t largest = i;
            std::size_t left = 2 * i + 1;
            std::size_t right = 2 * i + 2;

            if (left < count && data[left] > data[largest])
            {
                largest = left;
            }
            if (right < count && data[right] > data[largest])
            {
                largest = right;
            }
            if (largest == i)
            {
                break;
            }
            std::swap(data[i], data[largest]);
            i = largest;
        }
    }

public:
    /**
     * @brief Constructs an empty priority queue with a default capacity of 10.
     */
    PriorityQueue() : data(new T[10]), count(0), capacity(10) {}

    /**
     * @brief Constructs an empty priority queue with a given capacity.
     *
     * A capacity of 0 is treated as 1.
     *
     * @param cap Initial capacity of the priority queue.
     */
    explicit PriorityQueue(std::size_t cap)
        : data(new T[cap == 0 ? 1 : cap]), count(0), capacity(cap == 0 ? 1 : cap)
    {
    }

    /**
     * @brief Copy constructor. Performs a deep copy of the underlying buffer.
     *
     * @param other Priority queue to copy from.
     */
    PriorityQueue(const PriorityQueue& other)
        : data(new T[other.capacity]), count(other.count), capacity(other.capacity)
    {
        for (std::size_t i = 0; i < count; ++i)
        {
            data[i] = other.data[i];
        }
    }

    /**
     * @brief Copy assignment operator. Performs a deep copy of the underlying buffer.
     *
     * @param other Priority queue to copy from.
     * @return Reference to this priority queue.
     */
    PriorityQueue& operator=(const PriorityQueue& other)
    {
        if (this != &other)
        {
            T* newData = new T[other.capacity];
            for (std::size_t i = 0; i < other.count; ++i)
            {
                newData[i] = other.data[i];
            }
            delete[] data;
            data = newData;
            count = other.count;
            capacity = other.capacity;
        }
        return *this;
    }

    /**
     * @brief Destructor. Releases the underlying buffer.
     */
    ~PriorityQueue()
    {
        delete[] data;
    }

    /**
     * @brief Inserts a new key into the heap, growing the buffer if necessary.
     *
     * @param key Value to insert.
     */
    void insert(const T& key)
    {
        if (count == capacity)
        {
            resize();
        }
        data[count] = key;
        siftUp(count);
        ++count;
    }

    /**
     * @brief Removes and returns the maximum element.
     *
     * @return The maximum value in the priority queue.
     *
     * @throws std::underflow_error if the priority queue is empty.
     */
    T extractMax()
    {
        if (count == 0)
        {
            throw std::underflow_error("Priority queue is empty");
        }
        T root = data[0];
        data[0] = data[--count];
        siftDown(0);
        return root;
    }

    /**
     * @brief Returns a const reference to the maximum element without removing it.
     *
     * @return Const reference to the maximum value.
     *
     * @throws std::underflow_error if the priority queue is empty.
     */
    const T& getMax() const
    {
        if (count == 0)
        {
            throw std::underflow_error("Priority queue is empty");
        }
        return data[0];
    }

    /**
     * @brief Removes the element at heap index @p i, re-heapifying in
     * whichever direction is needed.
     *
     * Fixes a bug present in the original implementation: sifting down only
     * is not enough if the replacement value is larger than its new parent.
     *
     * @param i Index of the element to remove.
     *
     * @throws std::out_of_range if @p i is not a valid index.
     */
    void deleteKey(std::size_t i)
    {
        if (i >= count)
        {
            throw std::out_of_range("Invalid index");
        }
        T replaced = data[i];
        data[i] = data[--count];
        if (i < count)
        {
            if (data[i] > replaced)
            {
                siftUp(i);
            }
            else
            {
                siftDown(i);
            }
        }
    }

    /**
     * @brief Increases the value at heap index @p i to @p newValue and
     * restores the max-heap property.
     *
     * @param i Index of the element to update.
     * @param newValue New value, which must not be smaller than the current value.
     *
     * @throws std::out_of_range if @p i is not a valid index.
     * @throws std::invalid_argument if @p newValue is smaller than the current value.
     */
    void increaseKey(std::size_t i, const T& newValue)
    {
        if (i >= count)
        {
            throw std::out_of_range("Invalid index");
        }
        if (newValue < data[i])
        {
            throw std::invalid_argument("New value is smaller than the current value");
        }
        data[i] = newValue;
        siftUp(i);
    }

    /**
     * @brief Returns the number of elements currently stored.
     *
     * @return Current element count.
     */
    std::size_t size() const { return count; }

    /**
     * @brief Checks whether the priority queue has no elements.
     *
     * @return true if the priority queue is empty, false otherwise.
     */
    bool isEmpty() const { return count == 0; }

    /**
     * @brief Prints the heap's underlying array, space-separated, to standard
     * output. This is heap (array) order, not sorted order.
     */
    void display() const
    {
        for (std::size_t i = 0; i < count; ++i)
        {
            std::cout << data[i] << " ";
        }
        std::cout << std::endl;
    }
};
