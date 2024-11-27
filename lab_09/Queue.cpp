#include "Queue.h"

Queue::Queue(int capacity) :
	data_(new int[capacity]),
	head_(0), tail_(0), capacity_(capacity)
{}

Queue::~Queue() {
	delete [] data_;
}

void Queue::insert(const int& item) {

	if ((tail_ + 1) % capacity_ == head_) {
		cout << "Queue full!" << endl;
		return;
	}
	data_[tail_] = item;
	tail_ = (tail_ + 1) % capacity_;
}

int Queue::remove() {

	int x;
	if (head_ == tail_) {
		cout << "Underflow, do not use the returned value\n";
		// underflow still has to return something since this is
		// what the function says... until we add exceptions (later)
		return x;
	}
	x = data_[head_];
	head_ = (head_ + 1) % capacity_;
	return x;
}

void Queue::printAll() {

	if (head_ <= tail_) {
		for(int i = 0; i < head_; i++) cout << "X ";
		for(int i = head_; i < tail_; i++) cout << data_[i] << " ";
		for(int i = tail_; i < capacity_; i++) cout << "X ";
	}
	else {
		for(int i = 0; i < tail_; i++) cout << data_[i] << " ";
		for(int i = tail_; i < head_; i++) cout << "X ";
		for(int i = head_; i < capacity_; i++) cout << data_[i] << " ";
	}
	cout << endl;
}