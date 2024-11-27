#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
using std::cout;
using std::endl;

const int DEFAULT_CAPACITY = 5;

template<typename T>
class Queue {
public:
    // Constructor with default capacity
    Queue(int capacity = DEFAULT_CAPACITY) 
        : data_(new T[capacity]), head_(0), tail_(0), capacity_(capacity) {}

    // Destructor to release allocated memory
    ~Queue() {
        delete[] data_;
    }

    // Insert an element into the queue
    void insert(const T& item) {
        if ((tail_ + 1) % capacity_ == head_) {
            cout << "Queue full!" << endl;
            return;
        }
        data_[tail_] = item;
        tail_ = (tail_ + 1) % capacity_;
    }

    // Remove and return an element from the queue
    T remove() {
        if (head_ == tail_) {
            cout << "Underflow, do not use the returned value\n";
            return T(); // Return a default-constructed T
        }
        T x = data_[head_];
        head_ = (head_ + 1) % capacity_;
        return x;
    }

    // Print all elements in the queue for debugging
    void printAll() const {
        if (head_ <= tail_) {
            for (int i = 0; i < head_; i++) cout << "X ";
            for (int i = head_; i < tail_; i++) cout << data_[i] << " ";
            for (int i = tail_; i < capacity_; i++) cout << "X ";
        } else {
            for (int i = 0; i < tail_; i++) cout << data_[i] << " ";
            for (int i = tail_; i < head_; i++) cout << "X ";
            for (int i = head_; i < capacity_; i++) cout << data_[i] << " ";
        }
        cout << endl;
    }

private:
    T* data_;          // Pointer to queue data
    int head_;         // Index to the first element
    int tail_;         // Index to just past the last element
    int capacity_;     // Maximum capacity of the queue
};

#endif // QUEUE_H
