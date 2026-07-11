#pragma once

#include <cstddef>
#include <stdexcept>

/**
 * @brief Fixed-capacity array-based stack (LIFO).
 *
 * Elements are pushed and popped from the same end ("top"). The stack does
 * not grow automatically; once its capacity is reached, push() throws.
 *
 * @tparam T Type of element stored in the stack.
 */
template <typename T>
class Stack
{
private:
    T* data;
    std::size_t capacity;
    std::size_t topIndex; // number of elements currently stored

public:
    /**
     * @brief Constructs an empty stack with a default capacity of 10.
     */
    Stack() : data(new T[10]), capacity(10), topIndex(0) {}

    /**
     * @brief Constructs an empty stack with a given capacity.
     *
     * @param cap Maximum number of elements the stack can hold.
     *
     * @throws std::invalid_argument if @p cap is 0.
     */
    explicit Stack(std::size_t cap) : data(nullptr), capacity(cap), topIndex(0)
    {
        if (cap == 0)
        {
            throw std::invalid_argument("Stack capacity must be > 0");
        }
        data = new T[cap];
    }

    /**
     * @brief Copy constructor. Performs a deep copy of the underlying buffer.
     *
     * @param other Stack to copy from.
     */
    Stack(const Stack& other)
        : data(new T[other.capacity]), capacity(other.capacity), topIndex(other.topIndex)
    {
        for (std::size_t i = 0; i < topIndex; ++i)
        {
            data[i] = other.data[i];
        }
    }

    /**
     * @brief Copy assignment operator. Performs a deep copy of the underlying buffer.
     *
     * @param other Stack to copy from.
     * @return Reference to this stack.
     */
    Stack& operator=(const Stack& other)
    {
        if (this != &other)
        {
            T* newData = new T[other.capacity];
            for (std::size_t i = 0; i < other.topIndex; ++i)
            {
                newData[i] = other.data[i];
            }
            delete[] data;
            data = newData;
            capacity = other.capacity;
            topIndex = other.topIndex;
        }
        return *this;
    }

    /**
     * @brief Destructor. Releases the underlying buffer.
     */
    ~Stack()
    {
        delete[] data;
    }

    /**
     * @brief Pushes a value onto the top of the stack.
     *
     * @param value Value to push.
     *
     * @throws std::overflow_error if the stack is full.
     */
    void push(const T& value)
    {
        if (isFull())
        {
            throw std::overflow_error("Stack is full");
        }
        data[topIndex++] = value;
    }

    /**
     * @brief Removes and returns the top element.
     *
     * @return The value that was at the top of the stack.
     *
     * @throws std::underflow_error if the stack is empty.
     */
    T pop()
    {
        if (isEmpty())
        {
            throw std::underflow_error("Stack is empty");
        }
        return data[--topIndex];
    }

    /**
     * @brief Returns a reference to the top element.
     *
     * @return Reference to the top element.
     *
     * @throws std::underflow_error if the stack is empty.
     */
    T& stackTop()
    {
        if (isEmpty())
        {
            throw std::underflow_error("Stack is empty");
        }
        return data[topIndex - 1];
    }

    /**
     * @brief Returns a const reference to the top element.
     *
     * @return Const reference to the top element.
     *
     * @throws std::underflow_error if the stack is empty.
     */
    const T& stackTop() const
    {
        if (isEmpty())
        {
            throw std::underflow_error("Stack is empty");
        }
        return data[topIndex - 1];
    }

    /**
     * @brief Returns the number of elements currently stored.
     *
     * @return Current element count.
     */
    std::size_t size() const { return topIndex; }

    /**
     * @brief Checks whether the stack has no elements.
     *
     * @return true if the stack is empty, false otherwise.
     */
    bool isEmpty() const { return topIndex == 0; }

    /**
     * @brief Checks whether the stack has reached its capacity.
     *
     * @return true if the stack is full, false otherwise.
     */
    bool isFull() const { return topIndex == capacity; }
};
