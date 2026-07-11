#pragma once

#include <cstddef>
#include <iostream>
#include <stdexcept>

/**
 * @brief Circular-buffer queue (FIFO) that grows automatically when full.
 *
 * @tparam T Type of element stored in the queue.
 */
template <typename T>
class Queue
{
private:
    T* data;
    std::size_t capacity;
    std::size_t count;      // number of elements currently stored
    std::size_t frontIndex;
    std::size_t rearIndex;  // index where the next element will be written

    /**
     * @brief Reallocates the underlying circular buffer to a new capacity,
     * linearizing existing elements starting at index 0.
     *
     * @param newCapacity New capacity for the buffer.
     */
    void resize(std::size_t newCapacity)
    {
        T* newData = new T[newCapacity];
        for (std::size_t i = 0; i < count; ++i)
        {
            newData[i] = data[(frontIndex + i) % capacity];
        }
        delete[] data;
        data = newData;
        capacity = newCapacity;
        frontIndex = 0;
        rearIndex = count;
    }

public:
    /**
     * @brief Constructs an empty queue with a default capacity of 10.
     */
    Queue() : data(new T[10]), capacity(10), count(0), frontIndex(0), rearIndex(0) {}

    /**
     * @brief Constructs an empty queue with a given capacity.
     *
     * @param cap Initial capacity of the queue.
     *
     * @throws std::invalid_argument if @p cap is 0.
     */
    explicit Queue(std::size_t cap)
        : data(nullptr), capacity(cap), count(0), frontIndex(0), rearIndex(0)
    {
        if (cap == 0)
        {
            throw std::invalid_argument("Queue capacity must be > 0");
        }
        data = new T[cap];
    }

    /**
     * @brief Copy constructor. Performs a deep copy of the underlying buffer.
     *
     * @param other Queue to copy from.
     */
    Queue(const Queue& other)
        : data(new T[other.capacity]), capacity(other.capacity), count(other.count),
          frontIndex(0), rearIndex(other.count)
    {
        for (std::size_t i = 0; i < count; ++i)
        {
            data[i] = other.data[(other.frontIndex + i) % other.capacity];
        }
    }

    /**
     * @brief Copy assignment operator. Performs a deep copy of the underlying buffer.
     *
     * @param other Queue to copy from.
     * @return Reference to this queue.
     */
    Queue& operator=(const Queue& other)
    {
        if (this != &other)
        {
            T* newData = new T[other.capacity];
            for (std::size_t i = 0; i < other.count; ++i)
            {
                newData[i] = other.data[(other.frontIndex + i) % other.capacity];
            }
            delete[] data;
            data = newData;
            capacity = other.capacity;
            count = other.count;
            frontIndex = 0;
            rearIndex = count;
        }
        return *this;
    }

    /**
     * @brief Destructor. Releases the underlying buffer.
     */
    ~Queue()
    {
        delete[] data;
    }

    /**
     * @brief Adds a value to the rear of the queue.
     *
     * Grows the queue instead of throwing when full, so callers don't need
     * to pre-size it exactly.
     *
     * @param value Value to enqueue.
     */
    void enqueue(const T& value)
    {
        if (isFull())
        {
            resize(capacity * 2);
        }
        data[rearIndex] = value;
        rearIndex = (rearIndex + 1) % capacity;
        ++count;
    }

    /**
     * @brief Removes and returns the element at the front of the queue.
     *
     * @return The value that was at the front of the queue.
     *
     * @throws std::underflow_error if the queue is empty.
     */
    T dequeue()
    {
        if (isEmpty())
        {
            throw std::underflow_error("Queue is empty");
        }
        T value = data[frontIndex];
        frontIndex = (frontIndex + 1) % capacity;
        --count;
        return value;
    }

    /**
     * @brief Returns a reference to the element at the front of the queue.
     *
     * @return Reference to the front element.
     *
     * @throws std::underflow_error if the queue is empty.
     */
    T& front()
    {
        if (isEmpty())
        {
            throw std::underflow_error("Queue is empty");
        }
        return data[frontIndex];
    }

    /**
     * @brief Returns a const reference to the element at the front of the queue.
     *
     * @return Const reference to the front element.
     *
     * @throws std::underflow_error if the queue is empty.
     */
    const T& front() const
    {
        if (isEmpty())
        {
            throw std::underflow_error("Queue is empty");
        }
        return data[frontIndex];
    }

    /**
     * @brief Returns the number of elements currently stored.
     *
     * @return Current element count.
     */
    std::size_t size() const { return count; }

    /**
     * @brief Checks whether the queue has no elements.
     *
     * @return true if the queue is empty, false otherwise.
     */
    bool isEmpty() const { return count == 0; }

    /**
     * @brief Checks whether the queue has reached its capacity.
     *
     * @return true if the queue is full, false otherwise.
     */
    bool isFull() const { return count == capacity; }

    /**
     * @brief Prints the queue's elements, from front to rear, space-separated,
     * to standard output.
     */
    void display() const
    {
        for (std::size_t i = 0; i < count; ++i)
        {
            std::cout << data[(frontIndex + i) % capacity] << " ";
        }
        std::cout << std::endl;
    }
};
