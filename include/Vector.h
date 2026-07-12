#pragma once

#include <cstddef>
#include <stdexcept>

/**
 * @brief Dynamic array, similar in spirit to std::vector, implemented from scratch.
 *
 * Automatically grows its underlying buffer (doubling capacity) as elements
 * are appended via push_back().
 *
 * @tparam T Type of element stored in the vector.
 */
template <typename T>
class Vector
{
private:
    T* data;
    std::size_t len;
    std::size_t cap;

    /**
     * @brief Reallocates the underlying buffer to a new capacity, copying
     * existing elements over.
     *
     * @param newCap New capacity for the buffer.
     */
    void reallocate(std::size_t newCap)
    {
        T* newData = new T[newCap];
        for (std::size_t i = 0; i < len; ++i)
        {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
        cap = newCap;
    }

public:
    /**
     * @brief Constructs an empty vector with no allocated storage.
     */
    Vector() : data(nullptr), len(0), cap(0) {}

    /**
     * @brief Constructs an empty vector with pre-allocated storage.
     *
     * @param initialCapacity Number of elements to reserve space for up front.
     */
    explicit Vector(std::size_t initialCapacity)
        : data(initialCapacity > 0 ? new T[initialCapacity] : nullptr),
          len(0), cap(initialCapacity)
    {
    }

    /**
     * @brief Copy constructor. Performs a deep copy of the underlying buffer.
     *
     * @param other Vector to copy from.
     */
    Vector(const Vector& other)
        : data(other.cap > 0 ? new T[other.cap] : nullptr), len(other.len), cap(other.cap)
    {
        for (std::size_t i = 0; i < len; ++i)
        {
            data[i] = other.data[i];
        }
    }

    /**
     * @brief Copy assignment operator. Performs a deep copy of the underlying buffer.
     *
     * @param other Vector to copy from.
     * @return Reference to this vector.
     */
    Vector& operator=(const Vector& other)
    {
        if (this != &other)
        {
            T* newData = other.cap > 0 ? new T[other.cap] : nullptr;
            for (std::size_t i = 0; i < other.len; ++i)
            {
                newData[i] = other.data[i];
            }
            delete[] data;
            data = newData;
            len = other.len;
            cap = other.cap;
        }
        return *this;
    }

    /**
     * @brief Destructor. Releases the underlying buffer.
     */
    ~Vector()
    {
        delete[] data;
    }

    /**
     * @brief Appends a value to the end of the vector, growing the buffer
     * (doubling capacity, or allocating 1 slot from empty) if necessary.
     *
     * @param value Value to append.
     */
    void push_back(const T& value)
    {
        if (len == cap)
        {
            reallocate(cap == 0 ? 1 : cap * 2);
        }
        data[len++] = value;
    }

    /**
     * @brief Removes the last element of the vector.
     *
     * @throws std::underflow_error if the vector is empty.
     */
    void pop_back()
    {
        if (empty())
        {
            throw std::underflow_error("Vector is empty");
        }
        --len;
    }

    /**
     * @brief Returns a bounds-checked reference to the element at @p index.
     *
     * @param index Zero-based index of the element to access.
     * @return Reference to the element at @p index.
     *
     * @throws std::out_of_range if @p index is out of bounds.
     */
    T& at(std::size_t index)
    {
        if (index >= len)
        {
            throw std::out_of_range("Vector index out of range");
        }
        return data[index];
    }

    /**
     * @brief Returns a bounds-checked const reference to the element at @p index.
     *
     * @param index Zero-based index of the element to access.
     * @return Const reference to the element at @p index.
     *
     * @throws std::out_of_range if @p index is out of bounds.
     */
    const T& at(std::size_t index) const
    {
        if (index >= len)
        {
            throw std::out_of_range("Vector index out of range");
        }
        return data[index];
    }

    /**
     * @brief Returns a reference to the element at @p index without bounds checking.
     *
     * @param index Zero-based index of the element to access.
     * @return Reference to the element at @p index.
     */
    T& operator[](std::size_t index) { return data[index]; }

    /**
     * @brief Returns a const reference to the element at @p index without bounds checking.
     *
     * @param index Zero-based index of the element to access.
     * @return Const reference to the element at @p index.
     */
    const T& operator[](std::size_t index) const { return data[index]; }

    /**
     * @brief Returns a reference to the first element.
     *
     * @return Reference to the first element.
     *
     * @throws std::underflow_error if the vector is empty.
     */
    T& front()
    {
        if (empty())
        {
            throw std::underflow_error("Vector is empty");
        }
        return data[0];
    }

    /**
     * @brief Returns a reference to the last element.
     *
     * @return Reference to the last element.
     *
     * @throws std::underflow_error if the vector is empty.
     */
    T& back()
    {
        if (empty())
        {
            throw std::underflow_error("Vector is empty");
        }
        return data[len - 1];
    }

    /**
     * @brief Returns the number of elements currently stored.
     *
     * @return Current element count.
     */
    std::size_t size() const { return len; }

    /**
     * @brief Returns the number of elements the vector can hold without reallocating.
     *
     * @return Current capacity.
     */
    std::size_t capacity() const { return cap; }

    /**
     * @brief Checks whether the vector has no elements.
     *
     * @return true if the vector is empty, false otherwise.
     */
    bool empty() const { return len == 0; }

    /**
     * @brief Removes all elements without releasing the underlying buffer.
     */
    void clear() { len = 0; }

    /**
     * @brief Ensures the vector's capacity is at least @p newCap.
     *
     * Does nothing if the current capacity is already sufficient.
     *
     * @param newCap Minimum capacity to reserve.
     */
    void reserve(std::size_t newCap)
    {
        if (newCap > cap)
        {
            reallocate(newCap);
        }
    }

    // Minimal iterator support (range-for, sorting algorithms, etc.)

    /**
     * @brief Returns a pointer to the first element (begin iterator).
     *
     * @return Pointer to the first element.
     */
    T* begin() { return data; }

    /**
     * @brief Returns a pointer one past the last element (end iterator).
     *
     * @return Pointer one past the last element.
     */
    T* end() { return data + len; }

    /**
     * @brief Returns a const pointer to the first element (begin iterator).
     *
     * @return Const pointer to the first element.
     */
    const T* begin() const { return data; }

    /**
     * @brief Returns a const pointer one past the last element (end iterator).
     *
     * @return Const pointer one past the last element.
     */
    const T* end() const { return data + len; }
};
