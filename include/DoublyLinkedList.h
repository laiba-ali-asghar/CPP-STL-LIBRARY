#pragma once

#include <cstddef>
#include <iostream>
#include <stdexcept>

/**
 * @brief Doubly linked list node.
 *
 * @tparam T Type of value stored in the node.
 */
template <typename T>
class DNode
{
public:
    T data;
    DNode<T>* next;
    DNode<T>* prev;

    /**
     * @brief Constructs a node holding a default-constructed value with no
     * neighbors.
     */
    DNode() : data(T()), next(nullptr), prev(nullptr) {}

    /**
     * @brief Constructs a node holding @p val with no neighbors.
     *
     * @param val Value to store in the node.
     */
    explicit DNode(const T& val) : data(val), next(nullptr), prev(nullptr) {}
};

/**
 * @brief Circular doubly linked list.
 *
 * head->prev is always the tail, so both ends are reachable in O(1).
 *
 * @tparam T Type of element stored in the list.
 */
template <typename T>
class DoublyLinkedList
{
private:
    DNode<T>* head;
    std::size_t count;

public:
    /**
     * @brief Constructs an empty list.
     */
    DoublyLinkedList() : head(nullptr), count(0) {}

    /**
     * @brief Copy constructor. Performs a deep copy of all nodes.
     *
     * @param other List to copy from.
     */
    DoublyLinkedList(const DoublyLinkedList& other) : head(nullptr), count(0)
    {
        if (other.head == nullptr)
        {
            return;
        }
        DNode<T>* temp = other.head;
        do
        {
            insertAtTail(temp->data);
            temp = temp->next;
        } while (temp != other.head);
    }

    /**
     * @brief Copy assignment operator. Performs a deep copy of all nodes.
     *
     * @param other List to copy from.
     * @return Reference to this list.
     */
    DoublyLinkedList& operator=(const DoublyLinkedList& other)
    {
        if (this != &other)
        {
            clear();
            if (other.head != nullptr)
            {
                DNode<T>* temp = other.head;
                do
                {
                    insertAtTail(temp->data);
                    temp = temp->next;
                } while (temp != other.head);
            }
        }
        return *this;
    }

    /**
     * @brief Destructor. Deletes all nodes.
     */
    ~DoublyLinkedList()
    {
        clear();
    }

    /**
     * @brief Removes all elements from the list.
     */
    void clear()
    {
        while (head != nullptr)
        {
            removeAtHead();
        }
    }

    /**
     * @brief Inserts a new element at the front of the list.
     *
     * @param val Value to insert.
     */
    void insertAtHead(const T& val)
    {
        DNode<T>* newNode = new DNode<T>(val);
        if (head == nullptr)
        {
            newNode->next = newNode;
            newNode->prev = newNode;
            head = newNode;
        }
        else
        {
            DNode<T>* tail = head->prev;
            newNode->next = head;
            newNode->prev = tail;
            head->prev = newNode;
            tail->next = newNode;
            head = newNode;
        }
        ++count;
    }

    /**
     * @brief Inserts a new element at the end of the list.
     *
     * @param val Value to insert.
     */
    void insertAtTail(const T& val)
    {
        if (head == nullptr)
        {
            insertAtHead(val);
            return;
        }
        DNode<T>* newNode = new DNode<T>(val);
        DNode<T>* tail = head->prev;
        tail->next = newNode;
        newNode->prev = tail;
        newNode->next = head;
        head->prev = newNode;
        ++count;
    }

    /**
     * @brief Removes the element at the front of the list.
     *
     * @throws std::underflow_error if the list is empty.
     */
    void removeAtHead()
    {
        if (head == nullptr)
        {
            throw std::underflow_error("List is empty");
        }
        if (head->next == head)
        {
            delete head;
            head = nullptr;
        }
        else
        {
            DNode<T>* tail = head->prev;
            DNode<T>* oldHead = head;
            head = head->next;
            head->prev = tail;
            tail->next = head;
            delete oldHead;
        }
        --count;
    }

    /**
     * @brief Removes the element at the end of the list.
     *
     * @throws std::underflow_error if the list is empty.
     */
    void removeAtTail()
    {
        if (head == nullptr)
        {
            throw std::underflow_error("List is empty");
        }
        if (head->next == head)
        {
            delete head;
            head = nullptr;
            --count;
            return;
        }
        DNode<T>* tail = head->prev;
        DNode<T>* newTail = tail->prev;
        newTail->next = head;
        head->prev = newTail;
        delete tail;
        --count;
    }

    /**
     * @brief Removes the first node whose value equals @p val, if any.
     *
     * Does nothing if the list is empty or @p val is not found.
     *
     * @param val Value to search for and remove.
     */
    void remove(const T& val)
    {
        if (head == nullptr)
        {
            return;
        }
        DNode<T>* temp = head;
        do
        {
            if (temp->data == val)
            {
                if (temp == head)
                {
                    removeAtHead();
                }
                else if (temp == head->prev)
                {
                    removeAtTail();
                }
                else
                {
                    temp->prev->next = temp->next;
                    temp->next->prev = temp->prev;
                    delete temp;
                    --count;
                }
                return;
            }
            temp = temp->next;
        } while (temp != head);
    }

    /**
     * @brief Checks whether @p key exists in the list.
     *
     * @param key Value to search for.
     * @return true if a node with value @p key exists, false otherwise.
     */
    bool search(const T& key) const
    {
        if (head == nullptr)
        {
            return false;
        }
        DNode<T>* temp = head;
        do
        {
            if (temp->data == key)
            {
                return true;
            }
            temp = temp->next;
        } while (temp != head);
        return false;
    }

    /**
     * @brief Updates the value of the first node whose value equals @p key.
     *
     * @param key Value to search for.
     * @param val New value to assign.
     *
     * @throws std::runtime_error if the list is empty or @p key is not found.
     */
    void update(const T& key, const T& val)
    {
        if (head != nullptr)
        {
            DNode<T>* temp = head;
            do
            {
                if (temp->data == key)
                {
                    temp->data = val;
                    return;
                }
                temp = temp->next;
            } while (temp != head);
        }
        throw std::runtime_error("update: key not found");
    }

    /**
     * @brief Returns the number of elements currently stored.
     *
     * @return Current element count.
     */
    std::size_t countNodes() const { return count; }

    /**
     * @brief Checks whether the list has no elements.
     *
     * @return true if the list is empty, false otherwise.
     */
    bool isEmpty() const { return head == nullptr; }

    /**
     * @brief Prints the list's elements, space-separated, to standard output.
     */
    void display() const
    {
        if (head != nullptr)
        {
            DNode<T>* temp = head;
            do
            {
                std::cout << temp->data << " ";
                temp = temp->next;
            } while (temp != head);
        }
        std::cout << std::endl;
    }
};
